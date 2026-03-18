# Mapitron Web Sample

Install the build tools necessary for `mapitron` using [this guide](../../../BUILDING.md).

Install `node`.

```
npm install
npm run start
```

**Note: The vite environment is set up to watch changes in the `mapitron` library and reload the page.**

## Build Configurations

`mapitron` has a number of build configurations: `debug`, `release`, `relwithdebinfo`, and `minsizerel`.
Each of these build configurations is included in `mapitron`.
The `minsizerel` build is exported by default but this sample app is set up to load the build type as a query parameter.
For instance, `http://localhost:5173/?build=debug` loads the debug library.

The flip side of providing all four build configurations is that builds can take a long time.
When working with a specific build configuration, it is possible to only build/watch that configuration (e.g. `npm run start:debug`).