set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(GEN_CPP "${GEN_DIR}/shaderblobs.cpp")

add_custom_command(
  OUTPUT "${GEN_CPP}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"

  COMMAND ${CMAKE_COMMAND} -E echo "Generating shaders"
  COMMAND "$<TARGET_FILE:shadertron>" generate

  COMMAND ${CMAKE_COMMAND} -E echo "Compiling shaders"
  # TODO (stouff) actually compile

  COMMAND ${CMAKE_COMMAND} -E echo "Packing shaders"
  COMMAND ${CMAKE_COMMAND} -E make_directory "generated"
  COMMAND "$<TARGET_FILE:shadertron>" pack -i shaders/glsl -o ${GEN_CPP}

  DEPENDS shadertron
  COMMENT "Generating, compiling, and packing shaders"
  VERBATIM
)

set(SHADERBLOBS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public/shaderblobs/shaderblobs.hpp"
    "${GEN_CPP}"
)

add_custom_target(generate_shaderblobs DEPENDS "${GEN_CPP}")

add_library(shaderblobs ${SHADERBLOBS_FILES})

# Ensure generation happens before library compilation in all generators/IDEs
add_dependencies(shaderblobs generate_shaderblobs)