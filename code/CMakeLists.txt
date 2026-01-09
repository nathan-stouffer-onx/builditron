list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(BUILD_TESTS)
    include(CTest)
endif()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tools)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

add_subdirectory(samples)