#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

static constexpr char WIFI_SSID[] = "CSI_TX";
static constexpr char WIFI_PASS[] = "12345678";
static constexpr uint8_t RELAY_PIN = 5;
static constexpr size_t MOVING_WINDOW = 20;
static constexpr float DETECTION_THRESHOLD = 18.0f;
static constexpr uint32_t SAMPLE_INTERVAL_MS = 25;

volatile float g_lastAmplitude = 0.0f;
volatile bool g_newSample = false;

float ampWindow[MOVING_WINDOW] = {0.0f};
size_t ampIndex = 0;
size_t ampCount = 0;
float ampSum = 0.0f;
uint32_t lastPrintMs = 0;

static void wifiCsiCallback(void *ctx, wifi_csi_info_t *info) {
  if (info == nullptr || info->buf == nullptr || info->len <= 0) {
    return;
  }

  uint32_t sumAbs = 0;
  for (int i = 0; i < info->len; ++i) {
    sumAbs += abs(info->buf[i]);
  }

  g_lastAmplitude = static_cast<float>(sumAbs) / static_cast<float>(info->len);
  g_newSample = true;
}

static void initCsi() {
  wifi_csi_config_t csiConfig = {};
  csiConfig.lltf_en = true;
  csiConfig.htltf_en = true;
  csiConfig.stbc_htltf2_en = true;
  csiConfig.ltf_merge_en = true;
  csiConfig.channel_filter_en = true;
  csiConfig.manu_scale = false;
  csiConfig.shift = 4;

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_csi_rx_cb(wifiCsiCallback, nullptr);
  esp_wifi_set_csi_config(&csiConfig);
  esp_wifi_set_csi(true);
}

static float updateMovingAverage(float sample) {
  if (ampCount < MOVING_WINDOW) {
    ampWindow[ampIndex] = sample;
    ampSum += sample;
    ampCount++;
  } else {
    ampSum -= ampWindow[ampIndex];
    ampWindow[ampIndex] = sample;
    ampSum += sample;
  }

  ampIndex = (ampIndex + 1) % MOVING_WINDOW;
  return ampSum / static_cast<float>(ampCount);
}

static float computeVariance(float mean) {
  if (ampCount < 2) {
    return 0.0f;
  }

  float sumSq = 0.0f;
  for (size_t i = 0; i < ampCount; ++i) {
    float d = ampWindow[i] - mean;
    sumSq += d * d;
  }
  return sumSq / static_cast<float>(ampCount);
}

static void connectWifi() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  connectWifi();
  esp_wifi_set_ps(WIFI_PS_NONE);
  initCsi();

  Serial.println("CSI,raw_amp,avg_amp,var,state");
}

void loop() {
  if (!g_newSample) {
    delay(1);
    return;
  }

  noInterrupts();
  float sample = g_lastAmplitude;
  g_newSample = false;
  interrupts();

  const uint32_t now = millis();
  if (now - lastPrintMs < SAMPLE_INTERVAL_MS) {
    return;
  }
  lastPrintMs = now;

  const float average = updateMovingAverage(sample);
  const float variance = computeVariance(average);
  const bool humanDetected = variance > DETECTION_THRESHOLD;

  digitalWrite(RELAY_PIN, humanDetected ? HIGH : LOW);

  Serial.print("CSI,");
  Serial.print(sample, 2);
  Serial.print(",");
  Serial.print(average, 2);
  Serial.print(",");
  Serial.print(variance, 2);
  Serial.print(",");
  Serial.println(humanDetected ? "HUMAN" : "NO_HUMAN");
}
