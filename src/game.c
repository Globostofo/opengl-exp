#include "cglm/cglm.h"

#include "utils.h"
#include "load_shader.h"
#include "controls.h"

#include "game.h"

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat g_uv_buffer_data[] = {
    0.0f, 0.333f,
    0.333f, 0.333f,
    0.333f, 0.0f,
    0.333f, 0.0f,
    0.667f, 0.333f,
    0.667f, 0.0f,
    0.667f, 0.667f,
    0.333f, 0.333f,
    0.667f, 0.333f,
    0.333f, 0.0f,
    0.333f, 0.333f,
    0.667f, 0.333f,
    0.0f, 0.333f,
    0.333f, 0.0f,
    0.0f, 0.0f,
    0.667f, 0.667f,
    0.333f, 0.667f,
    0.333f, 0.333f,
    0.667f, 0.333f,
    0.667f, 0.667f,
    1.0f, 0.667f,
    0.667f, 0.0f,
    1.0f, 0.333f,
    1.0f, 0.0f,
    1.0f, 0.333f,
    0.667f, 0.0f,
    0.667f, 0.333f,
    0.333f, 0.667f,
    0.333f, 0.333f,
    0.0f, 0.333f,
    0.333f, 0.667f,
    0.0f, 0.333f,
    0.0f, 0.667f,
    1.0f, 0.333f,
    0.667f, 0.333f,
    1.0, 0.667f};

void play(GLFWwindow *window)
{
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    // Create and compile our GLSL program from the shaders
    GLuint programId = LoadShaders("res/shaders/vertex_shader.vert", "res/shaders/fragment_shader.frag");

    // Get a handle for our "MVP" uniform
    GLuint matrixId = glGetUniformLocation(programId, "MVP");

    mat4 projection, view, model, mvp;
    glm_mat4_identity(model);

    // Load the texture using any two methods
    // GLuint Texture = loadBMP_custom("uvtemplate.bmp");
    GLuint texture = load_dds("res/img/uvtemplate.dds");

    // Get a handle for our "myTextureSampler" uniform
    GLuint textureId = glGetUniformLocation(programId, "myTextureSampler");

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);

        compute_matrix_from_inputs(window, &projection, &view);

        glm_mat4_mul(projection, view, mvp);
        glm_mat4_mul(mvp, model, mvp); // Remember, matrix multiplication is the other way around

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(textureId, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,        // attribute. No particular reason for 1, but must match the layout in the shader.
            2,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programId);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vertexArrayId);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
