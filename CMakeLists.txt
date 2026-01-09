cmake_minimum_required(VERSION 3.22)

project(builditron VERSION 0.0.0 DESCRIPTION "A map viewer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# set so Visual Studio generates filters corresponding to folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(code)