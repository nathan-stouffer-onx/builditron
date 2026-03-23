# Windows Sample

Install the build tools necessary for `mapitron` using [this guide](../../../BUILDING.md).

Configure and build a windows destination using the pattern `dest-win-{vs|ninja}-{Debug|Release|RelWithDebInfo|MinSizeRel}`.

```
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

You can list available presets by running:

```
cmake --list-presets
```

Open the project in an appropriate editor.
