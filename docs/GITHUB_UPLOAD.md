# GitHub Upload Checklist

Before uploading to GitHub, keep source files and docs, but avoid committing build caches.

## Commit These

- `README.md`
- `tx_esp32/`
- `rx_esp32/`
- `src/`
- `python/`
- `docs/`
- `platformio.ini`
- `*.bat` helper scripts
- `.gitignore`

## Do Not Commit These

- `.venv/`
- `.pio/`
- `.platformio-core/`
- `rx_build.log`
- Python `__pycache__/`

## Suggested Git Commands

```bat
git init
git add .
git commit -m "Add ESP32 WiFi CSI human detection project"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO.git
git push -u origin main
```

Replace `YOUR_USERNAME` and `YOUR_REPO` with your GitHub details.
