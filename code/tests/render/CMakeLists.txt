enable_testing()

set(RENDER_TEST_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/render/line_layer_render_test.cpp"
)

add_executable(render-tests ${RENDER_TEST_FILES})

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${RENDER_TEST_FILES})

target_link_libraries(render-tests PRIVATE onyx GTest::gtest_main)

# set up cpp files with precompiled headers
target_precompile_headers(render-tests PRIVATE <vector> <gtest/gtest.h>)

include(GoogleTest)

# finds all the tests associated with the executable
gtest_discover_tests(render-tests)