#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
./gradlew :mapitron:assembleRelease
echo "AAR: mapitron/build/outputs/aar/mapitron-release.aar"
