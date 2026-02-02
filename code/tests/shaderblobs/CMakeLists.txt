set(SHADERBLOBS_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shaderblobs/load_tests.cpp"
)

add_executable(shaderblobs-tests ${SHADERBLOBS_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SHADERBLOBS_TEST_FILES})

target_link_libraries(shaderblobs-tests PRIVATE shaderblobs GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(shaderblobs-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(shaderblobs-tests)