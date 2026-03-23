# builditron

@README.md

@BUILDING.md

## awkwardness

`builditron` is cross-compiled so there is a _host_ machine and a _destination_ machine.
There are also some advanced dependencies because there are _host_ tools that are ran when building for the _destination_.
Many cross-compiling projects can build the _host_ tools once and then reuse them for _destination_ builds.
This is not ideal for `builditron` because the _host_ tools rely on frequently changing files -- requiring the _host_ to rebuild frequently.
It is a priority that building for a _destination_ machine automatically builds for the _host_ machine so that builds are never out of date.
This can be solved a number of ways.
The standard approach is to list the files that the _host_ depends on so CMake can rebuild the _host_ when any of those files change.
This requires a manual step tracking those files and does not last well over time.
`builditron` takes a non-standard approach that prioritizes convenience when building for the _destination_ machine.
When configurating for a runtime machine, there is a CMake script that identifies the host and configures for the host machine as well.
When building for a runtime machine, a special CMake target to build the _host_ tools is added.
That target depends on the same tool in the _destination_ build tree.
The _host_ target should be built in the exact scenarios where the _destination_ target should be built.
While the pattern is certainly not standard, it is correct for this use case and does not require brittle lists of files.