list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (MSVC AND CMAKE_GENERATOR MATCHES "Ninja")
  # Avoid C1041 when compiling in parallel: don't use a shared compile PDB.
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
endif()

# For target builds, configure and build host tools first
# This must happen before src/ so that shaderblobs can use the host-built shadertron
if(NOT MAPITRON_ADD_HOST_TOOLS)
  message(STATUS "Target build detected - configuring host")
  # TODO (stouff) set this up to identify the host

  set(HOST_PRESET "host-win-Debug")
  set(HOST_BINARY_DIR "${CMAKE_SOURCE_DIR}/out/build/${HOST_PRESET}")

  execute_process(
    COMMAND ${CMAKE_COMMAND} --preset ${HOST_PRESET}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE host_configure_result
  )

  if(NOT host_configure_result EQUAL 0)
      message(FATAL_ERROR "Host configure failed")
  endif()

  # Export the path to host-built tools for use by target build
  set(HOST_SHADERTRON_EXECUTABLE "${HOST_BINARY_DIR}/code/tools/shadertron/shadertron${CMAKE_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Path to host-built shadertron executable")
  message(STATUS "Host shadertron available at: ${HOST_SHADERTRON_EXECUTABLE}")
endif()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(tests)
add_subdirectory(samples)