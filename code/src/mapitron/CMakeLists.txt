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

# Link with embind for Emscripten builds
# TODO (stouff) see if typescript can be exported automatically
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    target_link_options(mapitron PUBLIC
        "SHELL:--bind"
        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME='createMapitronModule'"
    )
endif()