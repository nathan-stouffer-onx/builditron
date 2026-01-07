add_subdirectory(lucid)
add_subdirectory(styling)
add_subdirectory(engine)
add_subdirectory(onyx)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(render)
endif()