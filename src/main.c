#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"
#include "game.h"

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    if ((window = init()) == NULL)
        return -1;

    play(window);

    return 0;
}
