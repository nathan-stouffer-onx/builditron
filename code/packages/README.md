# packages

Platform-specific packages wrapping the `mapitron` library for distribution via native package registries.

## ios

A Swift Package containing an XCFramework built from the merged `libmapitron-ios.a` static library.
The XCFramework bundles slices for device (`ios-arm64`) and simulator (`ios-arm64-simulator`).
`bin/build_package.sh` automates assembling the framework after a CMake build.

## web

An npm package containing the compiled WASM module (`mapitron.js` / `mapitron.wasm`) and TypeScript declarations.
Build artifacts are copied here automatically as a CMake post-build step when building the `mapitron-wasm` target.
Each build configuration (Debug, Release, MinSizeRel, RelWithDebInfo) gets its own subdirectory under `src/`.
