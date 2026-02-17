# Publishing Guide

## First Time Setup

1. **Build the WASM artifacts:**
   ```bash
   # From repo root
   cmake --preset targ-emscripten-Release
   cmake --build --preset targ-emscripten-Release
   ```

2. **Verify the build artifacts:**
   ```bash
   ls -la code/packages/web/mapitron/src/
   # Should see: mapitron.js, mapitron.wasm, mapitron.d.ts
   ```

3. **Update package.json metadata:**
   - Set the author
   - Update the repository URL
   - Adjust the version as needed

## Testing Locally

Test the package in web-sample before publishing:

```bash
# From code/packages/web/mapitron
npm link

# From code/samples/web-sample
npm link mapitron
```

Now update `web-sample/src/main.ts` to import from `'mapitron'` instead of the local path.

## Publishing to npm

### First publish:

```bash
cd code/packages/web/mapitron

# Login to npm (one-time)
npm login

# Publish
npm publish
```

### Subsequent updates:

```bash
# Rebuild WASM
npm run build

# Bump version
npm version patch  # or minor, or major

# Publish
npm publish
```

## Scoped Package (Recommended)

For better namespacing, use a scoped package:

1. Update `package.json`:
   ```json
   "name": "@yourorg/mapitron"
   ```

2. Publish:
   ```bash
   npm publish --access public
   ```

## Automation

Consider adding to `.github/workflows/publish.yml`:
- Build WASM on release
- Run tests
- Auto-publish to npm
