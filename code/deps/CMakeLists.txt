include(FetchContent)

# declare and populate cmrc library (for packaging assets)
FetchContent_Declare(
  cmrc
  GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
  GIT_TAG 2.0.1
)
FetchContent_MakeAvailable(cmrc)

# declare and populate CLI11 library (for parsing command line args)
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG        v2.6.1
)
FetchContent_MakeAvailable(CLI11)

# set up lucid target
add_library(lucid INTERFACE)
target_include_directories(lucid INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lucid/include/interface")

if(BUILD_TESTS)
    # declare and populate googletest dependency
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()