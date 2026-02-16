# Mapitron Web Sample

This is a web sample app for Mapitron, demonstrating the WebAssembly-compiled mapitron library.

## Quick Start

Once your dev environment is set up:

```bash
npm install
npm run start
```

That's it! The app will be available at `http://localhost:5173`.

## Development Workflows

### Standard Development (Debug Build)

```bash
npm run start              # Starts dev server with Debug build (default)
```

### Using Different Build Types

```bash
npm run start:debug        # Debug build (larger, includes debug symbols)
npm run start:release      # Release build (optimized, smaller)
npm run start:relwithdebinfo  # Release with debug info
npm run start:minsizerel   # Minimum size release
```

### Running Tests

```bash
npm test                   # Run tests with Vitest
npm run test:ui            # Run tests with Vitest UI
npm run test:debug         # Test against Debug build
npm run test:release       # Test against Release build
```

### Building for Production

```bash
npm run build              # Production build (uses Debug by default)
npm run build:release      # Production build with Release WASM
```

## How It Works

The `mapitron` C++ library is compiled to WebAssembly by CMake. The generated `.wasm` and `.js` files are copied to build-type-specific subdirectories in `src/wasm/`:

- `src/wasm/debug/` - Debug build
- `src/wasm/release/` - Release build
- `src/wasm/relwithdebinfo/` - Release with debug info
- `src/wasm/minsizerel/` - Minimum size release

The app dynamically loads the appropriate build based on the `BUILD_TYPE` environment variable.

## Working with C++ Changes

If you modify the C++ code, you'll need to rebuild the WASM artifacts:

### From web-sample (recommended)

```bash
npm run cmake:build:debug     # Rebuild Debug build
npm run cmake:build:release   # Rebuild Release build
npm run cmake:build           # Rebuild both Debug and Release
```

### From project root

```bash
cmake --build --preset targ-emscripten-Debug
cmake --build --preset targ-emscripten-Release
```

The Vite dev server will automatically reload when the WASM files update.

## First-Time C++ Setup

If you haven't configured the C++ build yet:

```bash
npm run cmake:configure       # Configure all build types
npm run cmake:build           # Build Debug and Release
```

## Project Structure

```
web-sample/
├── src/
│   ├── main.ts              # Main application entry
│   ├── mapitron.test.ts     # Vitest tests
│   └── wasm/
│       ├── debug/           # Debug WASM build (generated)
│       ├── release/         # Release WASM build (generated)
│       └── mapitron.d.ts    # TypeScript definitions
├── package.json
└── vite.config.ts           # Vite + Vitest configuration
```

## Testing

Tests are written with Vitest and can call into the WASM module. See `src/mapitron.test.ts` for examples.

```typescript
import { describe, it, expect, beforeAll } from 'vitest';

describe('Mapitron', () => {
  let mapitron: any;

  beforeAll(async () => {
    const { default: createMapitronModule } = await import('./wasm/debug/mapitron.js');
    mapitron = await createMapitronModule();
  });

  it('should add numbers', () => {
    expect(mapitron.add(5, 3)).toBe(8);
  });
});
```
