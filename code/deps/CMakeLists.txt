# set up lucid target
add_library(lucid INTERFACE)
target_include_directories(lucid INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lucid/include/interface")