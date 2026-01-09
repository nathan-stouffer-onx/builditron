set(SHADERS_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shaders/load_tests.cpp"
)

add_executable(shaders-tests ${SHADERS_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SHADERS_TEST_FILES})

target_link_libraries(shaders-tests PRIVATE shaders GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(shaders-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(shaders-tests)