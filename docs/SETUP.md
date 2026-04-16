# Full Setup Guide

## Required Hardware

- 2x ESP32-WROOM development boards
- 2x USB cables
- optional relay module or LED on RX GPIO 5
- PC with Arduino IDE or PlatformIO

## Arduino IDE Setup

1. Install Arduino IDE 2.x.
2. Open Boards Manager.
3. Install `ESP32 by Espressif Systems`.
4. Select board `ESP32 Dev Module`.
5. Set upload speed to `115200` or `460800`.
6. Use Serial Monitor baud `115200`.

## Python Setup

Use the included helper:

```bat
setup_python_env.bat
```

Or install manually:

```bat
python -m pip install -r python\requirements.txt
```

## PlatformIO Setup

The project includes local PlatformIO helper scripts:

```bat
pio_tx_build.bat
pio_rx_build.bat
```

The scripts keep PlatformIO cache inside `.platformio-core` so the project remains portable.

## First Test Layout

Place boards like this:

```text
TX ESP32  <----- 1 to 5 meters ----->  RX ESP32
                 human movement path
```

Start simple:

- keep both boards on the same table height
- avoid metal objects near antennas
- keep TX and RX powered continuously
- move your hand/body between the boards
