#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>

static constexpr char AP_SSID[] = "CSI_TX";
static constexpr char AP_PASS[] = "12345678";
static constexpr uint8_t WIFI_CHANNEL = 6;
static constexpr uint16_t UDP_PORT = 5001;
static constexpr uint16_t PACKET_INTERVAL_MS = 2;

WiFiUDP udp;
IPAddress apIP(192, 168, 4, 1);
IPAddress apGateway(192, 168, 4, 1);
IPAddress apSubnet(255, 255, 255, 0);
IPAddress broadcastIP(192, 168, 4, 255);

const uint8_t payload[] = {
  0x43, 0x53, 0x49, 0x5F, 0x54, 0x58, 0x5F, 0x50,
  0x41, 0x43, 0x4B, 0x45, 0x54, 0x5F, 0x30, 0x31
};

void setup() {
  Serial.begin(115200);
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.setSleep(false);

  WiFi.softAPConfig(apIP, apGateway, apSubnet);
  WiFi.softAP(AP_SSID, AP_PASS, WIFI_CHANNEL, 0, 1);

  esp_wifi_set_ps(WIFI_PS_NONE);
  udp.begin(UDP_PORT);
}

void loop() {
  udp.beginPacket(broadcastIP, UDP_PORT);
  udp.write(payload, sizeof(payload));
  udp.endPacket();
  delay(PACKET_INTERVAL_MS);
}
