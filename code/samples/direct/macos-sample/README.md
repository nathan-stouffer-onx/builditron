# macOS Sample

Install the build tools necessary for `mapitron` using [this guide](../../../BUILDING.md).

Configure and build a macOS destination using the pattern `dest-mac-{Debug|Release|RelWithDebInfo|MinSizeRel}`.

```
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

You can list available presets by running:

```
cmake --list-presets
```

Open the project in an appropriate editor.