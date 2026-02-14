# Mapitron Web

This is the web frontend for Mapitron, using the WebAssembly-compiled mapitron library.

## Setup (One-time)

```bash
cd web
npm install
```

## Development

```bash
npm run dev
```

This starts a development server with hot reload. The app will be available at `http://localhost:5173`.

## Building

```bash
npm run build
```

Outputs to `dist/` directory.

## How It Works

The `mapitron` C++ library is compiled to WebAssembly by the main CMake build.
The generated `.wasm` and `.js` files are copied to `src/wasm/` and imported by this web project.

You don't need to know anything about C++ or CMake - just use standard web development tools!

## Updating the WebAssembly Library

If the C++ code changes, rebuild the Emscripten target:

```bash
# From the project root
cmake --build out/build/targ-emscripten-Release
```

The web dev server will automatically reload when the WASM files update.
