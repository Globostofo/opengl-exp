cmake_minimum_required(VERSION "3.28")

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(test_opengl
        VERSION 0.0.0
        LANGUAGES C)

add_subdirectory(src)
