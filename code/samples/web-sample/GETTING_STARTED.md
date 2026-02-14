# Getting Started with Mapitron Web

This guide is for web developers who want to use the Mapitron library in their web applications.

## Prerequisites

- Node.js (v18 or later)
- npm or yarn

**You do NOT need:**
- C++ compiler
- CMake
- Emscripten SDK

The WebAssembly files are pre-built and included in this project.

## Quick Start

### 1. Install Dependencies

```bash
cd web
npm install
```

### 2. Start Development Server

```bash
npm run dev
```

Open your browser to `http://localhost:5173`

### 3. Make Changes

Edit files in `src/`:
- `src/main.ts` - Your application code
- `src/style.css` - Styling
- `index.html` - HTML structure

The dev server will automatically reload when you save changes.

## Using the Mapitron API

```typescript
import createMapitronModule from './wasm/mapitron.js';

async function main() {
  // Load the WebAssembly module
  const mapitron = await createMapitronModule();

  // Use the API
  const result = mapitron.add(5, 3);
  console.log('5 + 3 =', result); // 8

  // Add a map layer
  mapitron.addLayer(JSON.stringify({
    id: 'my-layer',
    type: 'fill',
    source: 'my-source'
  }));

  // Load resources
  const programsLoaded = mapitron.loadPrograms();
  const fontInfo = mapitron.loadRoboto();

  // Clean up when done
  mapitron.shutdown();
}

main();
```

## TypeScript Support

The project includes TypeScript definitions in `src/wasm/mapitron.d.ts` for full type safety and autocomplete.

## Building for Production

```bash
npm run build
```

This creates optimized files in `dist/` ready for deployment.

## When the C++ Code Changes

If the core Mapitron C++ library is updated, you'll need to rebuild the WebAssembly files.

**Ask a C++ developer to:**
1. Build the Emscripten target: `cmake --build out/build/targ-emscripten-Release`
2. The new `.wasm` and `.js` files will automatically be copied to `src/wasm/`
3. Your dev server will auto-reload with the new version

You don't need to do anything else - just continue developing!

## Project Structure

```
web/
├── index.html          # Entry HTML file
├── package.json        # npm dependencies
├── tsconfig.json       # TypeScript configuration
├── vite.config.ts      # Vite bundler configuration
└── src/
    ├── main.ts         # Your application entry point
    ├── style.css       # Application styles
    └── wasm/           # WebAssembly files (generated)
        ├── mapitron.js    # JavaScript glue code
        ├── mapitron.wasm  # WebAssembly binary
        └── mapitron.d.ts  # TypeScript definitions
```

## Troubleshooting

### Module not found error

Make sure you've built the WebAssembly files first. Ask a C++ developer to run the build.

### Dev server won't start

Check that Node.js v18+ is installed: `node --version`

### TypeScript errors

Run `npm install` to ensure all dependencies are installed.

## Need Help?

Check the main project README or ask in the project discussions.
