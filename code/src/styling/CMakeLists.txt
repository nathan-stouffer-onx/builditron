set(STYLING_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/styling/parse/layer_json.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/styling/parse/layer_json.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/styling/layers/layer.hpp"
)

# add directory structure to IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${STYLING_FILES})

add_library(styling ${STYLING_FILES})

find_package(nlohmann_json CONFIG REQUIRED)

target_include_directories(styling
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
)

target_link_libraries(styling
    PUBLIC
    nlohmann_json::nlohmann_json
)