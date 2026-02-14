list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (MSVC AND CMAKE_GENERATOR MATCHES "Ninja")
  # Avoid C1041 when compiling in parallel: don't use a shared compile PDB.
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
endif()

# For target builds, configure host first -- his must happen before src/ so that shaderblobs can use the host-built shadertron
if(MAPITRON_IS_TARGET_BUILD)
  message(STATUS "Target build detected - configuring host")

  # Identify host platform
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(HOST_PLATFORM "win")
    set(HOST_EXECUTABLE_SUFFIX ".exe")
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(HOST_PLATFORM "mac")
    set(HOST_EXECUTABLE_SUFFIX "")
  else()
    message(FATAL_ERROR "Unsupported host platform: ${CMAKE_HOST_SYSTEM_NAME}")
  endif()

  set(HOST_PRESET "host-${HOST_PLATFORM}-MinSizeRel")
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
  set(HOST_SHADERTRON_EXECUTABLE "${HOST_BINARY_DIR}/code/tools/shadertron/shadertron${HOST_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Path to host-built shadertron executable")
  message(STATUS "Host shadertron path: ${HOST_SHADERTRON_EXECUTABLE}")
endif()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(tests)
add_subdirectory(samples)

# For Emscripten builds, copy WebAssembly artifacts to web directory
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set(WEB_WASM_DIR "${CMAKE_SOURCE_DIR}/web/src/wasm")

  add_custom_target(copy-wasm-to-web ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${WEB_WASM_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE:mapitron>"
      "${WEB_WASM_DIR}/mapitron.js"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$<TARGET_FILE_DIR:mapitron>/mapitron.wasm"
      "${WEB_WASM_DIR}/mapitron.wasm"
    DEPENDS mapitron
    COMMENT "Copying WebAssembly artifacts to web/src/wasm/"
  )
endif()