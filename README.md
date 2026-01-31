# builditron

An experiment in a better build system for the viewer.
This is meant to be a project with all the build complexity of the viewer but very little of the code complexity.
I am experimenting with some aspects of CMake to see how the viewer's build process could be improved.

## Highlights

* Transitive dependencies
    * CMake preserves transitive dependencies.
    This makes for much less verbose project configuration.
* Private headers/dependencies
    * We can be very specific about what headers/dependencies are exposed from a particular library.
    This improves modularization and build times (since they are not extraneously included).
    Additionally, it means the API library can be quite specific about what is exposed to the clients.
* Integration with vcpkg
    * CMake is quite easy to integrate with vcpkg and it monitors changes to the dependency file.
    This automates changes in dependencies and avoids bugs where developers need to manually update.
* Embedded static assets
    * CMake has easy tooling for embedding static assets directly into a library.
    This sidesteps the need for filesystem access which can be awkward on mobile platforms
* Embedded dynamic assets
    * CMake has infrastructure that allows executables to be ran at configure and build time to produce files that can be included in the application binary.
* Build configurations
    * CMake provides 4 build configurations out of the box: `Debug`, `Release`, `MinSizeRel`, and `RelWithDebInfo`.
    This makes local debugging easier and lays groundwork for easily posting multiple versions of our package for debugging on the clients
* Simpler cloud build
    * By simplifying the build process, we also enable a simpler cloudbuild (either CircleCI or GHA).
    We can matrix the workflow on the build configuration and reduce verbosity.
* Faster cloud build
    * CMake has integration with other tooling that makes caching quite effective in the cloud.
    Caching vcpkg results is trivial (something we have now but with some complexity).
    Using CMake would also unlock a tool called ccache that caches compiled object files across cloud runs and improves build times in the cloud.
* Presets
    * CMake easily exposes the ability to set up different configure/build commands via `CMakePresets.json`.
    We can define different presets for target platforms and compile settings without needing to remember anything for the command line.