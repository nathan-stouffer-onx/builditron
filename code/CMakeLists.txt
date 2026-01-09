list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tools)

add_subdirectory(tests)

add_subdirectory(samples)