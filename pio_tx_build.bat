@echo off
setlocal
set PLATFORMIO_CORE_DIR=%CD%\.platformio-core
".venv\Scripts\platformio.exe" run -e tx
