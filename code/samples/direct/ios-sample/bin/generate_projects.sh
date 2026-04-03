#!/bin/bash
set -e

REPO_ROOT="$(cd "$(dirname "$0")/../../../../.." && pwd)"
SAMPLES_DIR="$REPO_ROOT/code/samples/direct/ios-sample"

echo "Configuring CMake for simulator..."
cmake --preset dest-ios-simulator-xcode -S "$REPO_ROOT"

echo "Configuring CMake for device..."
cmake --preset dest-ios-device-xcode -S "$REPO_ROOT"

echo "Generating Xcode workspace..."
(cd "$SAMPLES_DIR" && tuist generate)
