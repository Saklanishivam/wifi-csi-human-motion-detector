# Upload Guide

## Upload Order

Always upload and power the transmitter first:

1. Upload TX firmware.
2. Keep TX powered on.
3. Upload RX firmware.
4. Open RX Serial Monitor at `115200`.

## Arduino IDE Upload

TX sketch:

```text
tx_esp32/tx_esp32.ino
```

RX sketch:

```text
rx_esp32/rx_esp32.ino
```

## PlatformIO Build

Build TX:

```bat
pio_tx_build.bat
```

Build RX:

```bat
pio_rx_build.bat
```

## PlatformIO Upload Commands

If you want manual upload commands, use:

```bat
set PLATFORMIO_CORE_DIR=.platformio-core
.venv\Scripts\platformio.exe run -e tx -t upload
.venv\Scripts\platformio.exe run -e rx -t upload
```

If upload fails, check:

- correct COM port
- USB cable supports data
- board boot button may need to be held during upload
- no Serial Monitor is using the port

## Expected RX Serial Output

```text
CSI,raw_amp,avg_amp,var,state
CSI,12.34,11.81,4.22,NO_HUMAN
CSI,19.91,14.56,28.40,HUMAN
```
