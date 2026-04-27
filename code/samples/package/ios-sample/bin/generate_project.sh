#!/bin/bash
set -e

SAMPLES_DIR="$(cd "$(dirname "$0")/.." && pwd)"

echo "Generating Xcode project..."
(cd "$SAMPLES_DIR" && tuist generate)
