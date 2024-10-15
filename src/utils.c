#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"

void handle_glfw_error(char *func_name)
{
    const char *description;
    int code = glfwGetError(&description);
    fprintf(stderr, "/!\\ GLFW error %i using %s: %s\n", code, func_name, description);
}

void handle_glew_error(int code, char *func_name)
{
    fprintf(stderr, "/!\\ GLEW error %i using %s: %s\n", code, func_name, glewGetErrorString(code));
}

int get_file_length(const FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return length;
}
