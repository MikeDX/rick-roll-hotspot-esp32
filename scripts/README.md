# Build Scripts

## build-web-firmware.sh

Builds firmware binaries for all ESP32 variants and prepares them for web installation via ESP Web Tools.

### Usage

```bash
./scripts/build-web-firmware.sh
```

### What it does

1. Builds firmware for all configured ESP32 environments:
   - ESP32 (standard)
   - ESP32-S2
   - ESP32-S3
   - ESP32-C6

2. Builds filesystem images (LittleFS) containing the rickroll GIF

3. Copies all binaries to `docs/firmware/`:
   - `*_firmware.bin` - Main application
   - `*_filesystem.bin` - LittleFS filesystem
   - `*_bootloader.bin` - Bootloader (if available)
   - `*_partitions.bin` - Partition table (if available)
   - `*_boot_app0.bin` - Boot app 0 (if available)

### Requirements

- PlatformIO installed and in PATH
- All dependencies installed (`pio lib install` if needed)
- Valid rickroll.gif file in `data/` directory

### Notes

- The script uses default partition layouts
- Filesystem offset is set to 0x180000 (1572864 bytes) for 4MB flash
- For different flash sizes, you may need to adjust manifest.json files

