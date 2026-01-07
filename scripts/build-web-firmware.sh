#!/bin/bash
# Build script for ESP Web Tools firmware binaries
# This script builds all ESP32 variants and prepares them for web flashing

# Don't exit on error - continue building other boards if one fails
set +e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
OUTPUT_DIR="$PROJECT_DIR/docs/firmware"
VERSION=$(date +"%Y.%m.%d")

echo "Building firmware for ESP Web Tools..."
echo "Version: $VERSION"
echo "Output directory: $OUTPUT_DIR"

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Array of environments to build
ENVIRONMENTS=(
    "esp32dev:ESP32"
    "esp32-s2-saola-1:ESP32-S2"
    "esp32-s3-devkitc-1:ESP32-S3"
    "esp32-c6-devkitc-1:ESP32-C6"
)

cd "$PROJECT_DIR"

# Build each environment
for env_info in "${ENVIRONMENTS[@]}"; do
    IFS=':' read -r env chip <<< "$env_info"
    echo ""
    echo "Building $chip ($env)..."
    
    # Build firmware and filesystem (continue on error)
    if ! pio run -e "$env"; then
        echo "  Warning: Firmware build failed for $chip ($env), skipping..."
        continue
    fi
    
    if ! pio run -e "$env" --target buildfs; then
        echo "  Warning: Filesystem build failed for $chip ($env), skipping..."
        continue
    fi
    
    # Find the build directory
    BUILD_DIR=".pio/build/$env"
    
    if [ ! -d "$BUILD_DIR" ]; then
        echo "Error: Build directory not found for $env"
        continue
    fi
    
    # Copy firmware binary
    if [ -f "$BUILD_DIR/firmware.bin" ]; then
        cp "$BUILD_DIR/firmware.bin" "$OUTPUT_DIR/${env}_firmware.bin"
        echo "  ✓ Copied firmware.bin"
    fi
    
    # Copy filesystem binary
    if [ -f "$BUILD_DIR/littlefs.bin" ]; then
        cp "$BUILD_DIR/littlefs.bin" "$OUTPUT_DIR/${env}_filesystem.bin"
        echo "  ✓ Copied filesystem.bin"
    elif [ -f "$BUILD_DIR/spiffs.bin" ]; then
        cp "$BUILD_DIR/spiffs.bin" "$OUTPUT_DIR/${env}_filesystem.bin"
        echo "  ✓ Copied filesystem.bin"
    fi
    
    # Copy bootloader and partitions if they exist (for ESP32)
    if [ -f "$BUILD_DIR/bootloader.bin" ]; then
        cp "$BUILD_DIR/bootloader.bin" "$OUTPUT_DIR/${env}_bootloader.bin"
        echo "  ✓ Copied bootloader.bin"
    fi
    
    if [ -f "$BUILD_DIR/partitions.bin" ]; then
        cp "$BUILD_DIR/partitions.bin" "$OUTPUT_DIR/${env}_partitions.bin"
        echo "  ✓ Copied partitions.bin"
    fi
    
    if [ -f "$BUILD_DIR/boot_app0.bin" ]; then
        cp "$BUILD_DIR/boot_app0.bin" "$OUTPUT_DIR/${env}_boot_app0.bin"
        echo "  ✓ Copied boot_app0.bin"
    fi
done

echo ""
echo "Build complete! Firmware files are in: $OUTPUT_DIR"

# Count successful builds
BUILT_COUNT=$(ls -1 "$OUTPUT_DIR"/*_firmware.bin 2>/dev/null | wc -l)
echo "Successfully built firmware for $BUILT_COUNT board(s)"

if [ "$BUILT_COUNT" -eq 0 ]; then
    echo "Warning: No firmware files were built!"
    exit 1
fi

# Exit with success if at least one board built successfully
exit 0

