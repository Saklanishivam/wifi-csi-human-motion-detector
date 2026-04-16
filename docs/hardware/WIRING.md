# Wiring Guide

## ESP32 Boards

Use two ESP32-WROOM boards:

- TX board sends WiFi traffic
- RX board receives CSI and controls output

## Relay or LED Output

RX output pin:

```text
GPIO 5
```

Relay wiring:

```text
RX GPIO 5 -> relay IN
RX GND    -> relay GND
Relay VCC -> relay power input
```

LED wiring:

```text
RX GPIO 5 -> 220 ohm resistor -> LED anode
LED cathode -> GND
```

## Safety Note

Do not connect AC mains directly to the ESP32. Use an isolated relay module rated for the load.
