set(SHADERTRON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shadertron/main.cpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SHADERTRON_FILES})

add_executable(shadertron ${SHADERTRON_FILES})

# add dependencies
target_link_libraries(shadertron
    PRIVATE
    shaders
    CLI11::CLI11
)