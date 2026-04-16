@echo off
setlocal

set PORT=%1
if "%PORT%"=="" set PORT=COM6

set BAUD=%2
if "%BAUD%"=="" set BAUD=115200

if not exist ".venv\Scripts\python.exe" (
  echo Local Python environment was not found.
  echo Run setup first or ask me to recreate the .venv.
  exit /b 1
)

".venv\Scripts\python.exe" "python\plot_serial.py" --port %PORT% --baud %BAUD%
