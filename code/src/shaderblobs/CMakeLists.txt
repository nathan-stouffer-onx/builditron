set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(GENERATED_RANGES "${GENERATED_DIR}/shaderblobs_ranges.inc")
set(GENERATED_BYTES "${GENERATED_DIR}/shaderblobs_bytes.inc")

add_custom_command(
  OUTPUT "${GENERATED_RANGES}" "${GENERATED_BYTES}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"

  COMMAND ${CMAKE_COMMAND} -E echo "Generating shaders"
  COMMAND "$<TARGET_FILE:shadertron>" generate

  COMMAND ${CMAKE_COMMAND} -E echo "Packing shaders"
  COMMAND ${CMAKE_COMMAND} -E make_directory "generated"
  COMMAND "$<TARGET_FILE:shadertron>" pack -i shaders/src -o generated

  DEPENDS shadertron
  COMMENT "Generating and packing shaders"
  VERBATIM
)

set(SHADERBLOBS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shaderblobs/load.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/shaderblobs/load.hpp"
)

add_custom_target(generate_shaderblobs DEPENDS "${GENERATED_RANGES}" "${GENERATED_BYTES}")

add_library(shaderblobs ${SHADERBLOBS_FILES})

target_include_directories(shaderblobs
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
    PRIVATE
        ${GENERATED_DIR}
)

# Ensure generation happens before library compilation in all generators/IDEs
add_dependencies(shaderblobs generate_shaderblobs)