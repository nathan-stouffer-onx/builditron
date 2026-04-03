#!/bin/bash
set -e

REPO_ROOT="$(cd "$(dirname "$0")/../../../../.." && pwd)"
PACKAGE_DIR="$REPO_ROOT/code/packages/ios/mapitron"
CONFIG="${1:-Release}"

SIM_BUILD="$REPO_ROOT/out/build/dest-ios-simulator-ninja"
DEVICE_BUILD="$REPO_ROOT/out/build/dest-ios-device-ninja"
HEADERS_DIR="$REPO_ROOT/out/build/ios-package-headers"

echo "Configuring CMake for simulator..."
cmake --preset dest-ios-simulator-ninja -S "$REPO_ROOT"

echo "Configuring CMake for device..."
cmake --preset dest-ios-device-ninja -S "$REPO_ROOT"

echo "Building mapitron for simulator ($CONFIG)..."
cmake --build "$SIM_BUILD" --config "$CONFIG" --target mapitron

echo "Building mapitron for device ($CONFIG)..."
cmake --build "$DEVICE_BUILD" --config "$CONFIG" --target mapitron

echo "Staging headers..."
rm -rf "$HEADERS_DIR"
mkdir -p "$HEADERS_DIR/mapitron"
cp "$REPO_ROOT/code/src/mapitron/include/public/mapitron/mapitron.hpp" "$HEADERS_DIR/mapitron/"
cp "$REPO_ROOT/code/src/mapitron/include/public/module.modulemap" "$HEADERS_DIR/"

echo "Creating XCFramework..."
rm -rf "$PACKAGE_DIR/mapitron.xcframework"
xcodebuild -create-xcframework \
    -library "$SIM_BUILD/lib/$CONFIG/libmapitron-ios.a" \
    -headers "$HEADERS_DIR" \
    -library "$DEVICE_BUILD/lib/$CONFIG/libmapitron-ios.a" \
    -headers "$HEADERS_DIR" \
    -output "$PACKAGE_DIR/mapitron.xcframework"

echo "Done: $PACKAGE_DIR/mapitron.xcframework"
