#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void handle_glfw_error(char *func_name);

void handle_glew_error(int code, char *func_name);

int get_file_length(const FILE *file);

#endif
