# shadertron

A host tool that generates and packs compiled shader blobs for embedding into the `shaderblobs` library.

## What it does

`shadertron generate` compiles the shader source assets from the `shaders` library into a build-time intermediate form.
`shadertron pack` takes those intermediates and packs them into `.inc` files that are `#include`d directly into `shaderblobs`.

## Host/destination interaction

`shadertron` runs on the host machine but its output is consumed by the destination build.
When building for a destination, CMake automatically builds `shadertron` on the host first (via the `HOST_SHADERTRON_EXECUTABLE` mechanism) before invoking it to produce the packed blobs.
This ensures the shader blobs are never stale without requiring a manual list of file dependencies.
See the [Awkwardness](../../../AGENTS.md#awkwardness) section in AGENTS.md for the broader pattern.
