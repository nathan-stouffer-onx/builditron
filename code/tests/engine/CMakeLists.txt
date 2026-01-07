enable_testing()

set(ENGINE_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/engine/caching/tile_cache_tests.cpp"
)

add_executable(engine-tests ${ENGINE_TEST_FILES})

# add private headers for complete testing
target_include_directories(engine-tests
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../src/viewer/engine/include/private"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${ENGINE_TEST_FILES})

target_link_libraries(engine-tests PRIVATE engine GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(engine-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(engine-tests)