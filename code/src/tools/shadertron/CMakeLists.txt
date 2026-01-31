set(SHADERTRON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shadertron/main.cpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SHADERTRON_FILES})

add_executable(shadertron ${SHADERTRON_FILES})

find_package(CLI11 CONFIG REQUIRED)

# add dependencies
target_link_libraries(shadertron
    PRIVATE
    shaders
    CLI11::CLI11
)