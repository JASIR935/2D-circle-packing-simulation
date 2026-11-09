cmake_minimum_required(VERSION 3.10)

project(geometrycomputations CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect files
file(GLOB LIBRARY_SOURCE_FILES library/src/*.cpp)
file(GLOB TEST_SOURCE_FILES library/test/*.cpp)
file(GLOB HEADER_FILES library/inc/*.h*)

# Export DLL symbols on Windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# GCC options
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -Wall -Wextra")
endif()

# Library
add_library(
    geometrykernel SHARED
    ${LIBRARY_SOURCE_FILES}
    ${HEADER_FILES}
)

# Main executable
add_executable(
    main
    main.cpp
)

# Tests
add_executable(
    geometrykernel_testrunner
    ${TEST_SOURCE_FILES}
)

# Include folders
target_include_directories(
    geometrykernel
    PUBLIC library/inc
)

target_include_directories(
    main
    PUBLIC library/inc
)

target_include_directories(
    geometrykernel_testrunner
    PUBLIC
        library/inc
        external
)

# Link library
target_link_libraries(
    main
    PUBLIC geometrykernel
)

target_link_libraries(
    geometrykernel_testrunner
    PUBLIC geometrykernel
)