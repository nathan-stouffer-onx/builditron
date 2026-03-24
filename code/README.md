# Structure

Each subdirectory contains a portion of the project and is described below.

## deps

A directory containing third party dependencies.
Some are just source code that have a CMake target wrapper around them (eg `lucid`).
Others are tools used by the build system (eg `vcpkg`).

## src

This directory contains the source code that makes up the library that is produced by this project.

## tests

This directory contains test projects for the core libraries.

## tools

This directory contains tooling that is typically ran on the host machine.

## packages

This directory contains that packages that can be pushed to a registry.
These same packages are used by the sample applications.

## samples

This directory contains sample applications utilizing the library for rapid testing and development.