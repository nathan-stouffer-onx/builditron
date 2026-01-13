cmake_minimum_required(VERSION 3.31)

project(builditron VERSION 0.0.0 DESCRIPTION "A map viewer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# set so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

enable_testing()

add_subdirectory(code)