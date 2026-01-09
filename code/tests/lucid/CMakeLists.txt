set(LUCID_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/lucid/scalar_tests.cpp"
)

add_executable(lucid-tests ${LUCID_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${LUCID_TEST_FILES})

target_link_libraries(lucid-tests PRIVATE lucid GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(lucid-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(lucid-tests)