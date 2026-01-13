include(FetchContent)

# declare and populate cmrc library (for packaging assets)
FetchContent_Declare(
  cmrc
  GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
  GIT_TAG 952ffddba731fc110bd50409e8d2b8a06abbd237
)
FetchContent_MakeAvailable(cmrc)

# set up lucid target
add_library(lucid INTERFACE)
target_include_directories(lucid INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lucid/include/interface")