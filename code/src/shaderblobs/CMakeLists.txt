set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(GENERATED_BYTES "${GENERATED_DIR}/shaderblobs_bytes.inc")
set(GENERATED_RANGES "${GENERATED_DIR}/shaderblobs_ranges.inc")

# Determine which shadertron executable to use
if(MAPITRON_IS_TARGET_BUILD)
  # Target build: use the host executable built via ExternalProject
  if(NOT DEFINED HOST_SHADERTRON_EXECUTABLE)
    message(FATAL_ERROR "HOST_SHADERTRON_EXECUTABLE not defined. Host tools should have been configured.")
  endif()
  set(SHADERTRON_EXE "${HOST_SHADERTRON_EXECUTABLE}")

  add_custom_command(
    OUTPUT "${SHADERTRON_EXE}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} --build --preset ${HOST_PRESET} --target shadertron

    DEPENDS shadertron
    COMMENT "Building shadertron for host"
    VERBATIM
  )
else()
  # Host build: use the local target
  set(SHADERTRON_EXE "$<TARGET_FILE:shadertron>")
endif()

add_custom_command(
  OUTPUT "${GENERATED_RANGES}" "${GENERATED_BYTES}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"

  COMMAND ${CMAKE_COMMAND} -E echo "Generating shaders"
  COMMAND "${SHADERTRON_EXE}" generate

  COMMAND ${CMAKE_COMMAND} -E echo "Packing shaders"
  COMMAND ${CMAKE_COMMAND} -E make_directory "generated"
  COMMAND "${SHADERTRON_EXE}" pack -i shaders/src -o generated

  DEPENDS "${SHADERTRON_EXE}"
  COMMENT "Generating and packing shaders"
  VERBATIM
)

set(SHADERBLOBS_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cpp/shaderblobs/load.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/public/shaderblobs/load.hpp"
)

add_custom_target(generate_shaderblobs DEPENDS "${SHADERTRON_EXE}" "${GENERATED_BYTES}" "${GENERATED_RANGES}")

add_library(shaderblobs ${SHADERBLOBS_FILES})

target_include_directories(shaderblobs
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/public"
    PRIVATE
        ${GENERATED_DIR}
)

# Ensure generation happens before library compilation in all generators/IDEs
add_dependencies(shaderblobs generate_shaderblobs)