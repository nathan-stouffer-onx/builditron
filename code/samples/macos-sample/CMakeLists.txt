set(MACOS_SAMPLE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/macos_sample/main.cpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${MACOS_SAMPLE_FILES})

add_executable(macos-sample ${MACOS_SAMPLE_FILES})

# add dependencies
target_link_libraries(macos-sample
    PRIVATE
    onyx
)