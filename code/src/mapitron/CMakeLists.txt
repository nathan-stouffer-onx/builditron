set(MAPITRON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/mapitron/mapitron.hpp"
)

# Add Emscripten bindings for web builds
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    list(APPEND MAPITRON_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp/bindings/embind.cpp"
    )
endif()

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${MAPITRON_FILES})

# Build as static library
add_library(mapitron ${MAPITRON_FILES})

target_include_directories(mapitron
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

# add dependencies
target_link_libraries(mapitron
    PUBLIC
        lucid
    PRIVATE
        engine
)

# For Emscripten, create a WASM module executable
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Create a wrapper executable that exports the library as a WASM module
    add_executable(mapitron-wasm ${MAPITRON_FILES})
    set_target_properties(mapitron-wasm PROPERTIES
        OUTPUT_NAME "mapitron"
        SUFFIX ".js"
    )

    target_include_directories(mapitron-wasm PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
    )

    target_link_libraries(mapitron-wasm
        PUBLIC
            lucid
        PRIVATE
            engine
    )

    # Link with embind for Emscripten builds
    target_link_options(mapitron-wasm PUBLIC
        "SHELL:--bind"
        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME='createMapitronModule'"
    )
endif()