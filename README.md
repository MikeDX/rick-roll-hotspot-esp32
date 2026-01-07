# ESP32 Rickroll Captive Portal 🎸

A harmless prank captive portal that broadcasts a "free wifi" network and serves a full-screen rickroll GIF when users connect. Built with Arduino framework for maximum portability across ESP32 boards.

![ESP32](https://img.shields.io/badge/ESP32-Compatible-blue)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Ready-orange)
![Arduino](https://img.shields.io/badge/Arduino-Framework-green)

## ⚠️ Disclaimer

**This project is for educational and harmless prank purposes only.**

- **Do NOT use this to intercept or monitor network traffic**
- **Do NOT use this in public spaces without proper authorization**
- **Do NOT use this to deceive or harm others**
- **Use responsibly and only in controlled environments (your own home, with friends' consent, etc.)**

The author and contributors are not responsible for any misuse of this software. Use at your own risk and in compliance with local laws and regulations.

## 🎯 Features

- **Full-screen rickroll** - No welcome messages, just pure rickroll
- **Instant captive portal** - Triggers immediately when devices connect
- **Cross-platform support** - Works with iOS, Android, Windows, and more
- **Multi-board compatible** - Supports ESP32, ESP32-S2, ESP32-S3, and ESP32-C6
- **Arduino framework** - Easy to understand and modify

## 📋 Requirements

- PlatformIO IDE (VS Code extension) or PlatformIO CLI
- ESP32 board (any variant)
- USB cable for programming
- A rickroll GIF file (included in `data/` directory)

## 🚀 Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/MikeDX/rick-roll-hotspot-esp32.git
cd rick-roll-hotspot-esp32
```

### 2. Install PlatformIO

- **VS Code**: Install the [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
- **CLI**: `pip install platformio`

### 3. Prepare Your GIF

Place your rickroll GIF file in the `data/` directory as `rickroll.gif`. A sample GIF is already included.

### 4. Build and Upload

**Option A: Web Installer (Easiest) 🌐**

Flash directly from your browser using our [web installer](https://mikedx.github.io/rick-roll-hotspot-esp32/):
1. Connect your ESP32 to your computer via USB
2. Visit the web installer page (requires Chrome or Edge)
3. Select your board type
4. Click install and follow the prompts
5. The firmware and filesystem will be flashed automatically!

> **Note:** The web installer is automatically built and deployed via GitHub Actions when code is pushed to the main branch.

**Option B: PlatformIO (Traditional) 🔧**

**For ESP32-C6:**
```bash
# Upload filesystem (contains the GIF)
pio run -e esp32-c6-devkitc-1 --target uploadfs

# Upload firmware
pio run -e esp32-c6-devkitc-1 --target upload

# Monitor serial output
pio device monitor -e esp32-c6-devkitc-1
```

**For other ESP32 boards**, replace `esp32-c6-devkitc-1` with:
- `esp32dev` - Standard ESP32
- `esp32-s2-saola-1` - ESP32-S2
- `esp32-s3-devkitc-1` - ESP32-S3

### 5. Connect and Enjoy

1. The ESP32 will create a WiFi network named **"free wifi"** (open, no password)
2. Connect to it from any device
3. Open any website - you'll be immediately rickrolled! 🎸

## 🔧 How It Works

1. **WiFi Access Point**: Creates an open WiFi network named "free wifi"
2. **DNS Server**: Intercepts all DNS queries and redirects them to the ESP32
3. **Captive Portal Detection**: Handles detection endpoints used by various operating systems:
   - Android: `/generate_204`, `/gen_204`
   - iOS: `/hotspot-detect.html`, `/library/test/success.html`
   - Windows: `/connecttest.txt`, `/ncsi.txt`
4. **Web Server**: Serves a full-screen HTML page with the rickroll GIF
5. **Instant Trigger**: DNS server processes requests immediately for fast triggering

## 📁 Project Structure

```
rick-roll-hotspot-esp32/
├── data/
│   └── rickroll.gif          # Your rickroll GIF file
├── docs/
│   ├── index.html            # Web installer page
│   └── firmware/             # Firmware binaries for web flashing
│       └── manifest.json     # ESP Web Tools manifest
├── scripts/
│   └── build-web-firmware.sh # Script to build web firmware
├── src/
│   └── main.cpp              # Main firmware code
├── platformio.ini           # PlatformIO configuration
├── README.md                 # This file
└── .gitignore               # Git ignore rules
```

## 🎛️ Supported Boards

The project includes multiple build environments in `platformio.ini`:

| Board | Environment | Notes |
|-------|-------------|-------|
| ESP32-C6 | `esp32-c6-devkitc-1` | Uses community fork for Arduino support |
| ESP32 | `esp32dev` | Standard ESP32 boards |
| ESP32-S2 | `esp32-s2-saola-1` | ESP32-S2 boards (Saola-1) |
| ESP32-S3 | `esp32-s3-devkitc-1` | ESP32-S3 boards |

## 🛠️ Customization

### Change WiFi SSID

Edit `src/main.cpp`:
```cpp
const char* ssid = "your-network-name";
```

### Use a Different GIF

1. Replace `data/rickroll.gif` with your GIF file
2. Re-upload the filesystem: `pio run -e <env> --target uploadfs`

### Modify the HTML

Edit the `index_html` constant in `src/main.cpp` to customize the page.

## 📚 Credits & Acknowledgments

- **ESP32 Arduino Core**: [espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)
- **PlatformIO**: [platformio/platformio-core](https://github.com/platformio/platformio-core)
- **ESP32-C6 Arduino Support**: [pioarduino/platform-espressif32](https://github.com/pioarduino/platform-espressif32) - Community fork enabling Arduino framework support for ESP32-C6
- **ESP Web Tools**: [esphome/esp-web-tools](https://github.com/esphome/esp-web-tools) - Browser-based firmware installer
- **Rick Astley**: For the iconic "Never Gonna Give You Up" that started it all 🎸

## 📝 License

This project is provided as-is for educational and entertainment purposes. Feel free to modify and use as you wish, but please:

- Use responsibly
- Respect others' privacy
- Follow local laws and regulations
- Don't use for malicious purposes

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest improvements
- Submit pull requests
- Share your modifications

## ⚡ Troubleshooting

**GIF not animating?**
- Make sure you uploaded the filesystem: `pio run -e <env> --target uploadfs`
- Try a hard refresh in your browser (Ctrl+F5 / Cmd+Shift+R)
- Verify the GIF file is valid and animated

**Captive portal not triggering?**
- Check serial monitor for errors
- Ensure DNS server started successfully
- Try disconnecting and reconnecting to the WiFi network

**Build errors?**
- Make sure PlatformIO is up to date
- Check that you're using the correct environment for your board
- Verify all dependencies are installed

## 📞 Support

If you encounter issues:
1. Check the [Issues](https://github.com/MikeDX/rick-roll-hotspot-esp32/issues) page
2. Review the troubleshooting section above
3. Open a new issue with details about your problem

---

**Remember**: This is a harmless prank project. Use responsibly and have fun! 🎉
