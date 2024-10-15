#include "utils.h"

#include "init.h"

int init_glfw()
{
    if (!glfwInit())
    {
        handle_glfw_error("glfwInit");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

    return 0;
}

GLFWwindow *create_window()
{
    GLFWwindow *window = glfwCreateWindow(800, 600, "Test OpenGL", NULL, NULL);
    if (window == NULL)
    {
        handle_glfw_error("glfwCreateWindow");
        glfwTerminate();
        return NULL;
    }
    return window;
}

GLFWwindow *init()
{
    GLFWwindow *window;
    int err_code;

    if (init_glfw())
        return NULL;
    window = create_window();
    if (window == NULL)
        return NULL;
    glfwMakeContextCurrent(window);
    glewExperimental = 1;

    err_code = glewInit();
    if (err_code != GLEW_OK)
    {
        handle_glew_error(err_code, "glewInit");
        return NULL;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return window;
}
