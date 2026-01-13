cmake_minimum_required(VERSION 3.22)

message(STATUS "CMAKE_VERSION=${CMAKE_VERSION}")
message(STATUS "BEFORE: CMAKE_MSVC_DEBUG_INFORMATION_FORMAT=${CMAKE_MSVC_DEBUG_INFORMATION_FORMAT}")

if (MSVC AND CMAKE_GENERATOR MATCHES "Ninja")
  # Avoid C1041 when compiling in parallel: don't use a shared compile PDB.
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
endif()

message(STATUS "AFTER: CMAKE_MSVC_DEBUG_INFORMATION_FORMAT=${CMAKE_MSVC_DEBUG_INFORMATION_FORMAT}")


project(builditron VERSION 0.0.0 DESCRIPTION "A map viewer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# set so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

add_subdirectory(code)