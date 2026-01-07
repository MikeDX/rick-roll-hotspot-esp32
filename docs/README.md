# Web Installer Documentation

This directory contains the GitHub Pages website for flashing firmware directly from your browser using [ESP Web Tools](https://esphome.github.io/esp-web-tools/).

## Structure

- `index.html` - Main web installer page
- `firmware/` - Directory containing firmware binaries and manifests
  - `manifest.json` - Main manifest file (auto-detects chip)
  - `manifest-*.json` - Board-specific manifests
  - `*.bin` - Firmware binaries (bootloader, partitions, app, filesystem)

## GitHub Pages Setup

### Using GitHub Actions (Recommended)

1. Go to your repository settings on GitHub
2. Navigate to "Pages" section
3. Under "Build and deployment", select **"GitHub Actions"**
4. The workflow will automatically build and deploy when you push changes

The website will be available at:
`https://mikedx.github.io/rick-roll-hotspot-esp32/`

### Manual Setup (Alternative)

If you prefer to deploy manually:

1. Go to repository settings → Pages
2. Select "Deploy from a branch"
3. Choose `main` branch and `/docs` folder
4. Save changes

## Building Firmware Locally

To build and prepare firmware binaries for web installation:

```bash
./scripts/build-web-firmware.sh
```

This script will:
1. Build firmware for all ESP32 variants
2. Build filesystem images
3. Copy all binaries to `docs/firmware/`
4. Update manifest files with version information

## Updating Firmware

When you make changes to the code:

1. Commit your changes
2. Push to GitHub
3. GitHub Actions will automatically:
   - Build firmware for all boards
   - Deploy to GitHub Pages
4. The website will update within a few minutes

## Manifest Format

The manifest files describe which firmware files to flash and where. Each build entry includes:
- `chipFamily` - ESP32 chip type (ESP32, ESP32-S2, ESP32-S3, ESP32-C6)
- `parts` - Array of firmware parts with file path and flash offset

For Arduino framework, typical offsets are:
- Bootloader: 0x1000 (4096)
- Partitions: 0x8000 (32768)
- Boot App 0: 0xE000 (57344)
- Application: 0x10000 (65536)
- Filesystem: Varies (typically 0x180000 / 1572864 for 4MB flash)

## Troubleshooting

**Firmware files not found:**
- Make sure GitHub Actions workflow completed successfully
- Check the Actions tab for build errors
- Verify file names match the manifest

**Web installer not working:**
- Ensure you're using HTTPS (required for Web Serial)
- Use Chrome or Edge browser
- Check browser console for errors
- Verify GitHub Pages is enabled and deployed

**GitHub Actions failing:**
- Check that PlatformIO can build all environments
- Verify all dependencies are specified in platformio.ini
- Check the Actions logs for specific error messages
