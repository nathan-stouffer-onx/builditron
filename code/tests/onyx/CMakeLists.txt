enable_testing()

set(ONYX_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/onyx/onyx_tests.cpp"
)

add_executable(onyx-tests ${ONYX_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${ONYX_TEST_FILES})

target_include_directories(onyx-tests PRIVATE "include/private")

find_package(GTest CONFIG REQUIRED)

target_link_libraries(onyx-tests PRIVATE onyx GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(onyx-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(onyx-tests)