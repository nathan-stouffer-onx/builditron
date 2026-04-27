# tests

Unit tests for the core libraries, organized to mirror the `src` structure.

| Directory | Tests for |
|---|---|
| `engine` | `engine` library |
| `lucid` | `lucid` dependency |
| `mapitron` | `mapitron` top-level library |
| `render` | rendering behavior (uses test assets) |
| `shaderblobs` | `shaderblobs` library |
| `shaders` | `shaders` library |
| `styling` | `styling` library |

Tests are run via CTest after building. From a configured build directory:

```
ctest --preset <preset-name>
```
