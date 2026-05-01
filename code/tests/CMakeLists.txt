include(CTest)

find_package(GTest CONFIG REQUIRED)

# On GHA, defer test discovery to ctest time to avoid build-time timeouts
# (e.g. Node.js startup latency for WASM tests on loaded Windows runners).
# With Xcode, POST_BUILD fails on Apple Silicon: Xcode links with -no_adhoc_codesign and
# codesigns the binary in a separate step after POST_BUILD scripts run, so the unsigned
# binary is killed when the discovery script tries to execute it.
# Locally with other generators, keep POST_BUILD so tests appear in the IDE immediately.
if(DEFINED ENV{GITHUB_ACTIONS} OR CMAKE_GENERATOR STREQUAL "Xcode" OR CMAKE_SYSTEM_NAME STREQUAL "iOS" OR ANDROID)
    set(GTEST_DISCOVER_SETTINGS DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30)
else()
    set(GTEST_DISCOVER_SETTINGS DISCOVERY_MODE POST_BUILD)
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