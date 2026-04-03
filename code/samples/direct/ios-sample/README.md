# ios-sample

A SwiftUI sample app that calls into mapitron via Swift C++ interop.

Separate Xcode projects are generated for simulator and device via [Tuist](https://tuist.io).

## Tools

In addition to the tools required for building mapitron, you will need:

- [Tuist](https://tuist.io): `brew install tuist`

## Generating the Xcode projects

From this directory:

```
bin/generate_projects.sh
```

This configures both CMake presets and generates:
- `ios-sample-simulator/ios-sample-simulator.xcodeproj`
- `ios-sample-device/ios-sample-device.xcodeproj`

## Building

Open the relevant `.xcodeproj` and click play. The pre-build scheme action will build mapitron before compiling the Swift app.