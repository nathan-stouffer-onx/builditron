cmake_minimum_required(VERSION 3.28.6)

# When externalNativeBuild invokes cmake without a preset, ANDROID_ABI is set on the
# command line but VCPKG_TARGET_TRIPLET is not. Map it before project() loads the toolchain.
if(ANDROID_ABI STREQUAL "arm64-v8a" AND NOT DEFINED CACHE{VCPKG_TARGET_TRIPLET})
    set(VCPKG_TARGET_TRIPLET "arm64-android" CACHE STRING "")
elseif(ANDROID_ABI STREQUAL "x86_64" AND NOT DEFINED CACHE{VCPKG_TARGET_TRIPLET})
    set(VCPKG_TARGET_TRIPLET "x64-android" CACHE STRING "")
endif()

project(builditron VERSION 0.0.0 DESCRIPTION "A map viewer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

option(MAPITRON_IS_DESTINATION_BUILD "Build is for a destination (as opposed to a host)" OFF)

add_subdirectory(code)