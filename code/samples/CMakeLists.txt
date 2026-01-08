if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(windows-sample)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory(macos-sample)
endif()