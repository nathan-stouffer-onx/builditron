include(FetchContent)

# set up lucid target
add_library(lucid INTERFACE)
target_include_directories(lucid INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lucid/include/interface")

# TODO (stouff) integrate this with vcpkg
# set up nlohmann target
add_library(nlohmann INTERFACE)
target_include_directories(nlohmann INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann/include/interface")

if(BUILD_TESTS)
    # declare and populate googletest dependency
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()