find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE HEADERS ${INCLUDE_DIRECTORY}/*.h)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	${GLEW_LIBRARIES}
)

add_executable(main
               load_shader.c
               utils.c
               init.c
               game.c
               main.c
               ${HEADERS}
)
target_include_directories(main PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(main ${ALL_LIBS})
