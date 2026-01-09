find_package(GTest CONFIG REQUIRED)

add_subdirectory(lucid)
add_subdirectory(styling)
add_subdirectory(shaders)
add_subdirectory(engine)
add_subdirectory(onyx)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(render)
endif()