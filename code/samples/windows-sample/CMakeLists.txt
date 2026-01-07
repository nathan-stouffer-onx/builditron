set(WINDOWS_SAMPLE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/windows_sample/main.cpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${WINDOWS_SAMPLE_FILES})

add_executable(windows-sample ${WINDOWS_SAMPLE_FILES})

# add dependencies
target_link_libraries(windows-sample
    PRIVATE
    onyx
)