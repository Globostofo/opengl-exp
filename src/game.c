#include "cglm/cglm.h"

#include "load_shader.h"

#include "game.h"

static const GLfloat g_vertex_buffer_data[] = {-1.f, -1.f, 0.f, 1.f, -1.f, 0.f, 0.f, 1.f, 0.f};

void play(GLFWwindow *window)
{
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    // Create and compile our GLSL program from the shaders
    GLuint programId = LoadShaders("res/shaders/vertex_shader.vert", "res/shaders/fragment_shader.frag");

    // Get a handle for our "MVP" uniform
    GLuint matrixId = glGetUniformLocation(programId, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    mat4 projection;
    glm_perspective(glm_rad(45.0f), 4.0f / 3.0f, 0.1f, 100.0f, projection);
    // Or, for an ortho camera :
    // glm_ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f, projection); // In world coordinates

    // Camera matrix
    mat4 view;
    glm_lookat(
        (vec3){4, 3, 3}, // Camera is at (4,3,3), in World Space
        (vec3){0, 0, 0}, // and looks at the origin
        (vec3){0, 1, 0}, // Head is up (set to 0,-1,0 to look upside-down)
        view
    );
    // Model matrix : an identity matrix (model will be at the origin)
    mat4 model;
    glm_mat4_identity(model);
    // Our ModelViewProjection : multiplication of our 3 matrices
    mat4 mvp;
    glm_mat4_mul(projection, view, mvp);
    glm_mat4_mul(mvp, model, mvp); // Remember, matrix multiplication is the other way around

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);

        // Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexArrayId);
    glDeleteProgram(programId);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
