set(ONYX_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/onyx/onyx.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/onyx/onyx.hpp"
)

# TODO use some strategy similar to this to add platform-specific code
# if (WIN32)
#     list(APPEND FRAG_FILES
#         "${CMAKE_CURRENT_SOURCE_DIR}/cpp/onyx/onyx_windows.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/public/onyx/onyx_windows.hpp"
#     )
# elseif (APPLE)
#     list(APPEND FRAG_FILES
#         "${CMAKE_CURRENT_SOURCE_DIR}/cpp/onyx/onyx_macos.cpp"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/public/onyx/onyx_macos.hpp"
#     )
# endif()

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${FRAG_FILES})

add_library(onyx ${ONYX_FILES})

target_include_directories(onyx
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

# add dependencies
target_link_libraries(onyx
    PUBLIC
        lucid
    PRIVATE
        styling
)