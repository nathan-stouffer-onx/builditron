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

    # Convert build type to lowercase for directory name
    string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

    set(WEB_WASM_DIR "${CMAKE_SOURCE_DIR}/code/samples/web-sample/src/wasm/${BUILD_TYPE_LOWER}")
    set(NPM_PACKAGE_DIR "${CMAKE_SOURCE_DIR}/code/packages/web/mapitron/src")

    # Copy WebAssembly artifacts after building mapitron-wasm
    add_custom_command(TARGET mapitron-wasm POST_BUILD
        # Copy to web-sample for local development (build-type-specific subdirectory)
        COMMAND ${CMAKE_COMMAND} -E make_directory "${WEB_WASM_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:mapitron-wasm>"
            "${WEB_WASM_DIR}/mapitron.js"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:mapitron-wasm>/mapitron.wasm"
            "${WEB_WASM_DIR}/mapitron.wasm"
        # Copy TypeScript definitions to build-type subdirectory
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NPM_PACKAGE_DIR}/mapitron.d.ts"
            "${WEB_WASM_DIR}/mapitron.d.ts"
        # Also copy to root wasm directory for convenience
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NPM_PACKAGE_DIR}/mapitron.d.ts"
            "${CMAKE_SOURCE_DIR}/code/samples/web-sample/src/wasm/mapitron.d.ts"
        # Copy to npm package for publishing
        COMMAND ${CMAKE_COMMAND} -E make_directory "${NPM_PACKAGE_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:mapitron-wasm>"
            "${NPM_PACKAGE_DIR}/mapitron.js"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:mapitron-wasm>/mapitron.wasm"
            "${NPM_PACKAGE_DIR}/mapitron.wasm"
    )
endif()