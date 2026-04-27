if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(windows-sample)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory(macos-sample)
endif()

# The iOS sample is a hand-written Xcode project at ios-sample/.
# It is not managed by CMake -- see ios-sample/README.md for setup instructions.