set(MAPITRON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/mapitron/mapitron.hpp"
)

# TODO conditionally add platform-specific files here

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${MAPITRON_FILES})

# Build as static library
add_library(mapitron ${MAPITRON_FILES})

target_include_directories(mapitron
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

target_compile_definitions(mapitron
    PUBLIC
        MAPITRON_BUILD_TYPE="$<CONFIG>"
)

# add dependencies
target_link_libraries(mapitron
    PUBLIC
        lucid
    PRIVATE
        engine
)

# For iOS, merge all static libraries into one for easy consumption by the sample app
# and for packaging into an XCFramework
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    find_package(protobuf CONFIG REQUIRED)
    add_custom_command(TARGET mapitron POST_BUILD
        COMMAND libtool -static -o "$<TARGET_FILE_DIR:mapitron>/libmapitron-ios.a"
            "$<TARGET_FILE:mapitron>"
            "$<TARGET_FILE:engine>"
            "$<TARGET_FILE:styling>"
            "$<TARGET_FILE:shaders>"
            "$<TARGET_FILE:shaderblobs>"
            "$<TARGET_FILE:engine_assets>"
            "$<TARGET_FILE:shaders_json>"
            "$<TARGET_FILE:protobuf::libprotobuf>"
        COMMENT "Merging static libraries into libmapitron-ios.a"
        VERBATIM
    )
endif()

# For Emscripten, create a WASM module executable
if(EMSCRIPTEN)
    # Create a wrapper executable that exports the library as a WASM module
    set(MAPITRON_WASM_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp/bindings/embind.cpp"
    )

    add_executable(mapitron-wasm ${MAPITRON_WASM_FILES})
    set_target_properties(mapitron-wasm PROPERTIES
        OUTPUT_NAME "mapitron"
        SUFFIX ".js"
    )

    target_include_directories(mapitron-wasm PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
    )

    target_link_libraries(mapitron-wasm
        PUBLIC
            mapitron
    )

    # Link with embind for Emscripten builds
    target_link_options(mapitron-wasm PUBLIC
        "SHELL:--bind"
        "SHELL:--emit-tsd mapitron.d.ts"
        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME='createMapitronModule'"
    )

    set(NPM_PACKAGE_DIR "${CMAKE_SOURCE_DIR}/code/packages/web/mapitron/src")
    set(NPM_BUILD_DIR "${NPM_PACKAGE_DIR}/${CMAKE_BUILD_TYPE}")

    # Copy WebAssembly artifacts after building mapitron-wasm
    add_custom_command(TARGET mapitron-wasm POST_BUILD
        # Copy build-type-specific artifacts to their subdirectory
        COMMAND ${CMAKE_COMMAND} -E make_directory "${NPM_BUILD_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:mapitron-wasm>"
            "${NPM_BUILD_DIR}/mapitron.js"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:mapitron-wasm>/mapitron.wasm"
            "${NPM_BUILD_DIR}/mapitron.wasm"
        # The generated .d.ts is shared across build types
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:mapitron-wasm>/mapitron.d.ts"
            "${NPM_PACKAGE_DIR}/mapitron.d.ts"
    )
endif()

if(ANDROID)
    set(MAPITRON_JNI_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp/bindings/jnibind.cpp"
    )

    add_library(mapitron-jni SHARED ${MAPITRON_JNI_FILES})
    target_link_libraries(mapitron-jni PRIVATE mapitron android log)
endif()