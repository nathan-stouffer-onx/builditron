# builditron

@README.md

@BUILDING.md

`builditron` is cross-compiled so there is a _host_ machine and a _runtime_ machine.
There are also some advanced dependencies because there are _host_ tools that are ran when building for the _runtime_.
Many cross-compiling projects can build the host tools once and then reuse them for runtime builds.
This is not ideal for `builditron` because the host tools rely on frequently changing files -- requiring the host to rebuild frequently.
It is a priority that building for a _runtime_ machine automatically builds for the _host_ machine so that builds are never out of date.
This can be solved a number of ways.
The standard approach is to list the files that the host depends on so CMake can rebuild the host when any of those files change.
This requires a manual step tracking those files and does not last well over time.
`builditron` takes a non-standard approach that prioritizes convenience when building for the runtime machine.
When configurating for a runtime machine, there is a CMake script that identifies the host and configures for the host machine as well.
When building for a runtime machine, a special CMake target to build the host tools is added.
That target depends on the runtime target of the same tool.
The host target should be built in the exact scenarios where the runtime target of the same name should be built.
While the pattern is certainly not standard, it is correct for this use case and does not require brittle lists of files.