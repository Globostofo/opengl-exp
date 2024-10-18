cmake_minimum_required(VERSION "3.28")

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(test_opengl
        VERSION 0.0.0
        LANGUAGES C)

file(COPY res DESTINATION "${CMAKE_BINARY_DIR}")

add_subdirectory(external/cglm)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    ${GLEW_LIBRARIES}
    cglm
)

add_executable(main
               ${SOURCES}
               ${HEADERS}
)
target_include_directories(main PUBLIC include/)
target_link_libraries(main ${ALL_LIBS} -lm)
