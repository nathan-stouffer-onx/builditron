set(SHADERS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shaders/load.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/shaders/load.hpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SHADERS_FILES})

cmrc_add_resource_library(
    shaders_json
    NAMESPACE shaders_json
    WHENCE .
    assets/shaders/json/TiledPseudoRasters/Plinth.json
)

add_library(shaders ${SHADERS_FILES})

find_package(nlohmann_json CONFIG REQUIRED)

target_include_directories(shaders
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

target_link_libraries(shaders
    PUBLIC
        nlohmann_json::nlohmann_json
    PRIVATE
        shaders_json
)