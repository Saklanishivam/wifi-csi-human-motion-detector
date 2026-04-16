@echo off
setlocal

where python >nul 2>nul
if errorlevel 1 (
  echo Python was not found in PATH.
  echo Install Python 3.10+ first, then run:
  echo   python -m pip install -r python\requirements.txt
  exit /b 1
)

python -m pip install --upgrade pip
python -m pip install -r python\requirements.txt

echo.
echo Python dependencies installed.
echo Example:
echo   python python\plot_serial.py --port COM6 --baud 115200
