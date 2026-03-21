# Building

The primary build artifact of this repository is the `mapitron` library.
This is what could be built and posted to a package registry.
In addition to the package, this repository contains tests and sample applications utilizing `mapitron`.
These integrate directly with each target's native development system. 
This document outlines the build process for the library itself; more can be read about the sample apps [here](./code/samples/README.md).

`mapitron` is often cross-compiled.
There is a target machine (where the code will run) and a host machine (where the code is built).
Additionally, building the _target_ requires tools that are built/ran on the _host_ machine.
When setting up the build environment, tools to build both the host and target must be installed.
Even if the target machine is the same as the host, the project will deal them separately and still expects host tools to be installed.

## Tools

A few tools are required regardless of which platform you are building:

* `git`
* `cmake`
* `ninja`

After your initial clone (or whenever submodules are updated), you must run the following to sync the submodules:

```
git submodule update --init
```

### Hosts

The host builds tools that are needed during a target build.
The following tools must be installed:

- Windows
    - Visual Studio
- macOS
    - clang/clang++
- Linux
    - gcc/g++

### Targets

The target is the platform on which the code will run.
The following tools must be installed:

- Windows
    - Visual Studio
- Web
    - make

Additional steps for each target type are listed below.

#### Web

To build for web, the C++ code is compiled to WASM by [emscripten](https://emscripten.org/).
The necessary tooling is included as a submodule at `code/deps/emsdk`.
Before your first web build, install and activate it:

```
cd code/deps/emsdk
./emsdk install latest
./emsdk activate latest
```

## Building

Once all required tools are installed, it is possible to build `mapitron`!

This repository uses CMake presets to manage configurations.
All presets are defined in [CMakePresets.json](CMakePresets.json) and the files under [presets/](./presets/).

Preset names follow the pattern `{host|targ}-{platform}-{Debug|Release|RelWithDebInfo|MinSizeRel}`.
For example:
- `host-mac-Debug` — macOS host build, debug configuration
- `targ-emscripten-Release` — Emscripten target build, release configuration

Configure and build the `mapitron` library using a preset:

```
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

You can list available presets by running:

```
cmake --list-presets
```