#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void handle_glfw_error(char *func_name);

void handle_glew_error(int code, char *func_name);

int get_file_length(FILE *file);

GLuint load_dds(const char *imagepath);

#endif
