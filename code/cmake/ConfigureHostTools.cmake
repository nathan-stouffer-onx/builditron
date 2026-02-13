# TODO (stouff) set this up to identify the host
# TODO (stouff) set this up so that modifications trigger a reconfigure
message(STATUS "Configuring host")

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