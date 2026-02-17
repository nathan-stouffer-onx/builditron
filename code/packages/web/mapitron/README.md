# Mapitron

WebAssembly-powered map rendering library built with C++ and Emscripten.

## Installation

```bash
npm install mapitron
```

## Usage

```typescript
import createMapitronModule from 'mapitron';

// Initialize the WASM module
const mapitron = await createMapitronModule();

// Use the library
// (Add your API usage examples here)
```

## Development

This package is built from C++ source using Emscripten. The build process:

1. C++ code is compiled to WebAssembly
2. Emscripten generates JavaScript bindings using embind
3. TypeScript definitions are included for type safety

## Building from Source

From the repository root:

```bash
# Configure CMake with Emscripten preset
cmake --preset targ-emscripten-Release

# Build the project
cmake --build --preset targ-emscripten-Release
```

The WASM artifacts will be automatically copied to this package's `src/` directory.

## License

MIT
