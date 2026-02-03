set(MAPITRON_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron_tests.cpp"
)

add_executable(mapitron-tests ${MAPITRON_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${MAPITRON_TEST_FILES})

target_include_directories(mapitron-tests PRIVATE "include/private")

target_link_libraries(mapitron-tests PRIVATE mapitron GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(mapitron-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(mapitron-tests)