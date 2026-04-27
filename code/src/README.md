# src

The source libraries that make up `mapitron`.

## mapitron

The top-level library and the primary build artifact of this repository.
Exposes the public API and links the internal libraries together.
On iOS, a post-build step merges all static libraries into a single `libmapitron-ios.a` for easy packaging.
On Emscripten, a companion `mapitron-wasm` executable wraps the library as a WASM module.

## engine

The core rendering engine.
Handles tile caching, shader programs, and font loading.
Depends on `styling`, `shaders`, `shaderblobs`, and `lucid`.

## styling

Parses style definitions (e.g. layer JSON) into typed layer objects consumed by the engine.

## shaders

Manages shader source assets and exposes load/generate functions.
Shader JSON and handwritten GLSL assets are embedded directly into the library via `cmrc`.

## shaderblobs

Compiles shader sources into packed binary blobs at build time using `shadertron`.
The generated blobs are embedded as `.inc` files and loaded at runtime without filesystem access.
See [tools/shadertron](../tools/shadertron/README.md) for details on the code generation step.
