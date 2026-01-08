set(ENGINE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/engine/brain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/engine/caching/tile_cache.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private/engine/caching/tile_cache.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/engine/brain.hpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${ENGINE_FILES})

add_library(engine ${ENGINE_FILES})

target_include_directories(engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
)

# add dependencies
target_link_libraries(engine
    PUBLIC
        lucid
        styling
)