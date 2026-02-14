cmake_minimum_required(VERSION 3.28)

project(builditron VERSION 0.0.0 DESCRIPTION "A map viewer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# set so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

option(MAPITRON_IS_TARGET_BUILD "Build is for a target (as opposed to a host)" OFF)

# Validate EMSDK environment variable for Emscripten builds
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  if(NOT DEFINED ENV{EMSDK})
    message(FATAL_ERROR
      "EMSDK environment variable is not set. "
      "Please set it in your environment. "
      "Example: export EMSDK=/path/to/emsdk")
  endif()
  message(STATUS "Building for Emscripten with EMSDK=$ENV{EMSDK}")
endif()

add_subdirectory(code)