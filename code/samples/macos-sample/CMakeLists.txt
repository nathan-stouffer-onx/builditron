set(MACOS_SAMPLE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/macos_sample/main.cpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${MACOS_SAMPLE_FILES})

file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/../assets" "${CMAKE_CURRENT_BINARY_DIR}/assets" SYMBOLIC)

add_executable(macos-sample ${MACOS_SAMPLE_FILES})

# add dependencies
target_link_libraries(macos-sample
    PRIVATE
    onyx
)

add_dependencies(macos-sample shadertron)