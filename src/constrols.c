#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controls.h"

double lastTime = 0.0;
// position
vec3 position = {0, 0, -5};
// horizontal angle : toward -Z
float horizontalAngle = 0.0f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float fov = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.003f;

void compute_matrix_from_inputs(GLFWwindow *window, mat4 *projection, mat4 *view)
{
    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Reset mouse position for next frame
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width / 2, height / 2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * (((float)width) / 2 - xpos);
    verticalAngle += mouseSpeed * (((float)height) / 2 - ypos);
    verticalAngle = glm_clamp(verticalAngle, -3.1416/2, 3.1416/2);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    vec3 direction = {
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)};

    // Right vector
    vec3 right = {
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)};

    // Up vector
    vec3 up;
    glm_vec3_cross(right, direction, up);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        glm_vec3_muladds(direction, deltaTime*speed, position);
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        glm_vec3_muladds(direction, -deltaTime*speed, position);
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        glm_vec3_muladds(right, deltaTime*speed, position);
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        glm_vec3_muladds(right, -deltaTime*speed, position);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm_perspective(glm_rad(fov), 4.0f / 3.0f, 0.1f, 100.0f, projection);

    // Camera matrix
    vec3 look_target;
    glm_vec3_add(position, direction, look_target);
    glm_lookat(
        position,       // Camera is here
        look_target,    // and looks here : at the same position, plus "direction"
        up,             // Head is up (set to 0,-1,0 to look upside-down)
        view
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}
