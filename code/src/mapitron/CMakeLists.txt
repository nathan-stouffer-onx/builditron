set(MAPITRON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/mapitron/mapitron.hpp"
)

# TODO use some strategy similar to this to add platform-specific code
# if (WIN32)
#     list(APPEND MAPITRON_FILES
#         "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron_windows.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/public/mapitron/mapitron_windows.hpp"
#     )
# elseif (APPLE)
#     list(APPEND MAPITRON_FILES
#         "${CMAKE_CURRENT_SOURCE_DIR}/cpp/mapitron/mapitron_macos.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/public/mapitron/mapitron_macos.hpp"
#     )
# endif()

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