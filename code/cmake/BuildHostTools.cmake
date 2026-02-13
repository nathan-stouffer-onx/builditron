# TODO (stouff) set this up to identify the host
# TODO (stouff) set this up so that modifications trigger a reconfigure
message(STATUS "Configuring host")

set(HOST_PRESET "host-win-Debug")

execute_process(
  COMMAND ${CMAKE_COMMAND} --preset ${HOST_PRESET}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE host_configure_result
)

if(NOT host_configure_result EQUAL 0)
    message(FATAL_ERROR "Host configure failed")
endif()

message(STATUS "Building host")

execute_process(
  COMMAND ${CMAKE_COMMAND} --build --preset ${HOST_PRESET}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE host_build_result
)

if(NOT host_build_result EQUAL 0)
    message(FATAL_ERROR "Host build failed")
endif()