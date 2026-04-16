# Python Plotter

The plotter reads RX serial CSV output and shows live graphs.

## Install

```bat
setup_python_env.bat
```

## Run

```bat
run_plot.bat COM6 115200
```

Replace `COM6` with your RX ESP32 serial port.

## Direct Command

```bat
.venv\Scripts\python.exe python\plot_serial.py --port COM6 --baud 115200
```

## Serial Format

The plotter expects lines like:

```text
CSI,raw_amp,avg_amp,var,state
CSI,12.34,11.81,4.22,NO_HUMAN
CSI,19.91,14.56,28.40,HUMAN
```
