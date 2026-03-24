include(CTest)

find_package(GTest CONFIG REQUIRED)

# On GHA, defer test discovery to ctest time to avoid build-time timeouts
# (e.g. Node.js startup latency for WASM tests on loaded Windows runners).
# Locally, keep the default POST_BUILD so tests appear in the IDE immediately after building.
if(DEFINED ENV{GITHUB_ACTIONS})
    set(GTEST_DISCOVERY_MODE "DISCOVERY_MODE PRE_TEST")
else()
    set(GTEST_DISCOVERY_MODE "DISCOVERY_MODE POST_BUILD")
endif()

add_subdirectory(lucid)
add_subdirectory(styling)
add_subdirectory(shaders)
add_subdirectory(shaderblobs)
add_subdirectory(engine)
add_subdirectory(mapitron)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(render)
endif()