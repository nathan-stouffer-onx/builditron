enable_testing()

set(STYLING_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/styling/parse/layer_json_tests.cpp"
)

add_executable(styling-tests ${STYLING_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${STYLING_TEST_FILES})

target_link_libraries(styling-tests PRIVATE styling GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(lucid-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(styling-tests)