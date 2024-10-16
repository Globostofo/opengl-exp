cmake_minimum_required(VERSION "3.28")

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(test_opengl
        VERSION 0.0.0
        LANGUAGES C)

file(COPY res DESTINATION "${CMAKE_BINARY_DIR}")

set(INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)
