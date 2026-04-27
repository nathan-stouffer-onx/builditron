# ios-sample (package)

A SwiftUI sample app that links mapitron via the Swift package in `code/packages/ios/mapitron`.

## First-time setup

The Swift package wraps a binary XCFramework that must be built before opening the project.
Swift Package Manager resolves packages before any build actions run, so the XCFramework
must exist on disk first.

### 1. Build the package

From the repo root:

```
code/packages/ios/mapitron/bin/build_package.sh
```

This configures both CMake presets (simulator and device), builds `libmapitron-ios.a` for
each, and assembles them into `code/packages/ios/mapitron/mapitron.xcframework`.

An optional configuration argument can be passed (defaults to `Release`):

```
code/packages/ios/mapitron/bin/build_package.sh Debug
```

### 2. Generate and open the Xcode project

From the repo root:

```
code/samples/package/ios-sample/bin/generate_project.sh
```

Then open the generated `ios-sample.xcodeproj` and build.

## Rebuilding after C++ changes

The Xcode scheme includes a pre-action that automatically runs `build_package.sh` before
each build, so hitting Play keeps the XCFramework up to date without any manual steps.
