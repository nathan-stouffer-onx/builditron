# Mapitron Web Sample

This is a web sample app for Mapitron, demonstrating the WebAssembly-compiled mapitron library.

## Quick Start

Once your dev environment is set up:

```bash
npm install
npm run start
```

That's it!
- The C++ code is automatically built in Debug mode
- The dev server starts at `http://localhost:5173`
- **Hot reload:** Edit any C++ file and the browser automatically reloads with the new build

## What Happens When You Run `npm start`

1. Builds the C++ mapitron library to WebAssembly (Debug mode)
2. Starts the Vite dev server
3. Watches C++ files (`code/src/**/*.{cpp,hpp}`) for changes
4. On C++ change: rebuilds WASM → Vite detects change → browser reloads

**Zero manual steps for web developers!**

## Development Workflows

### Standard Development

```bash
npm run start              # Debug build with auto-rebuild on C++ changes
npm run start:nocpp        # Start Vite only (no C++ watching)
npm run start:novite       # Watch and build C++ only (no dev server)
```

### Using Different Build Types

```bash
npm run start:debug        # Debug build with hot reload (default)
npm run start:release      # Release build with hot reload
npm run start:relwithdebinfo  # Release with debug info + hot reload
npm run start:minsizerel   # Minimum size release + hot reload
```

### Building for Production

```bash
npm run build              # Automatically builds C++ (Release) then bundles
```

The C++ build happens automatically - no manual CMake commands needed!

### Running Tests

```bash
npm test                   # Run tests with Vitest
npm run test:ui            # Run tests with Vitest UI
npm run test:debug         # Test against Debug build
npm run test:release       # Test against Release build
```

## How It Works

### Automatic C++ Building

- **`npm start`**: Runs `prestart` script → builds C++ Debug → starts dev server + file watcher
- **`npm build`**: Runs `prebuild` script → builds C++ Release → bundles for production
- **File watching**: Monitors `code/src/` and `code/include/` for C++ changes

### Hot Reload Flow

```
C++ file saved
  ↓
chokidar detects change
  ↓
CMake rebuilds WASM
  ↓
WASM files updated in src/wasm/debug/
  ↓
Vite detects WASM change
  ↓
Browser hot reloads
```

### Build Type Organization

The C++ library is compiled to WebAssembly and copied to build-type-specific subdirectories:

- `src/wasm/debug/` - Debug build (larger, with debug symbols)
- `src/wasm/release/` - Release build (optimized, smaller)
- `src/wasm/relwithdebinfo/` - Release with debug info
- `src/wasm/minsizerel/` - Minimum size release

The app dynamically loads the appropriate build based on the `BUILD_TYPE` environment variable.

## Manual C++ Building (Advanced)

Most developers won't need this - the npm scripts handle it automatically (including auto-configure).

```bash
npm run cmake:build:debug     # Auto-configures if needed, then builds Debug
npm run cmake:build:release   # Auto-configures if needed, then builds Release
npm run cmake:build           # Builds both Debug and Release
```

If you want to configure all build types at once (optional):

```bash
npm run cmake:configure       # Configure all build types at once
```

Or from the project root:

```bash
cmake --preset targ-emscripten-Debug      # Configure Debug
cmake --build --preset targ-emscripten-Debug  # Build Debug
```

## Project Structure

```
web-sample/
├── src/
│   ├── main.ts              # Main application entry
│   ├── mapitron.test.ts     # Vitest tests
│   └── wasm/
│       ├── debug/           # Debug WASM build (auto-generated)
│       ├── release/         # Release WASM build (auto-generated)
│       └── mapitron.d.ts    # TypeScript definitions (copied from npm package)
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

## TypeScript Definitions

The TypeScript definitions (`mapitron.d.ts`) are maintained in the npm package at:
- **Source of truth:** `code/packages/web/mapitron/src/mapitron.d.ts`
- **Web-sample copy:** `code/samples/web-sample/src/wasm/mapitron.d.ts` (auto-copied by CMake)

Edit the npm package version, and it will automatically sync to web-sample on the next C++ build.

## Troubleshooting

### First time running?

Just run:

```bash
npm install
npm run start
```

Everything (CMake configure, C++ build, dev server) happens automatically! No manual setup needed.

### C++ not rebuilding?

The file watcher monitors `code/src/` and `code/include/`. If your C++ files are elsewhere, update the watch pattern in `package.json`:

```json
"cpp:watch:debug": "chokidar \"../../src/**/*.{cpp,hpp}\" \"../../include/**/*.hpp\" -c \"npm run cmake:build:debug\""
```

### Want to disable auto-rebuild?

```bash
npm run start:nocpp          # Start Vite without C++ watching
```
