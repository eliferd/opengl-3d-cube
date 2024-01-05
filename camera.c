#include <cglm.h>
#include <math.h>
#include "camera.h"
#include "window.h"
#include "shader.h"

float xPos = 0.0;
float yPos = 0.0;
float zPos = -3.0;

vec3 cameraPos = {0.0, 0.0, 3.0};
vec3 direction;

float deltaTime = 0.0f,
      lastFrame = 0.0f;

void sendMatricesToOpenGL(const unsigned int shaderProgramId)
{
    // Intialize matrices
    mat4 modelMatrix = GLM_MAT4_IDENTITY_INIT;
    mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;
    mat4 projectionMatrix = GLM_MAT4_IDENTITY_INIT;

    // Synchronize camera movements with computer's CPU speed
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 3.0f * deltaTime;

    // Intialize camera vectors
    vec3 cameraFront = {0.0, 0.0, -1.0}; // a.k.a cameraOrientation (yaw / pitch)
    vec3 cameraUp = {0.0, 1.0, 0.0};
    vec3 camPosFront = {}; // a.k.a cameraPosition + cameraFront (cameraOrientation)

    direction[0] = cos(glm_rad(mouseX/*YAW*/)) * cos(glm_rad(mouseY /*PITCH*/)); // x
    direction[1] = sin(glm_rad(mouseY /*PITCH*/));                               // y
    direction[2] = sin(glm_rad(mouseX/*YAW*/)) * cos(glm_rad(mouseY /*PITCH*/)); // z

    // We normalize the direction we are looking at to the cameraFront vector.
    // The direction vector is calculated in the window file with the mouse event.
    glm_vec3_normalize_to(direction, cameraFront);

    // camPosFront = cameraPos + cameraFront
    // It must be done before handling keys for movements. Otherwise it will not take the new cameraPos / direction for the movements.
    glm_vec3_add(cameraPos, cameraFront, camPosFront);

    // Key handles for movements;
    if(glfwGetKey(get_window(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        vec3 target = {};
        glm_vec3_scale(cameraFront, cameraSpeed, target);
        glm_vec3_add(cameraPos, target, cameraPos);
    }
    if(glfwGetKey(get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        vec3 target = {};
        glm_vec3_scale(cameraFront, cameraSpeed, target);
        glm_vec3_sub(cameraPos, target, cameraPos);
    }
    if(glfwGetKey(get_window(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        vec3 target = {};
        glm_vec3_cross(cameraFront, cameraUp, target);
        glm_vec3_normalize(target);

        glm_vec3_scale(target, cameraSpeed, target);
        glm_vec3_sub(cameraPos, target, cameraPos);
    }
    if(glfwGetKey(get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        vec3 target = {};
        glm_vec3_cross(cameraFront, cameraUp, target);

        glm_vec3_normalize(target);

        glm_vec3_scale(target, cameraSpeed, target);
        glm_vec3_add(cameraPos, target, cameraPos);
    }

    glm_lookat(cameraPos, camPosFront, cameraUp, viewMatrix);

    // set camera type (perspective)
    glm_perspective(glm_rad(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f, projectionMatrix);

    setModelMatrix(modelMatrix);
    setViewMatrix(viewMatrix);
    setProjectionMatrix(projectionMatrix);
}

void setModelMatrix(mat4 modelMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(get_shader_program_id(), "modelMatrix"), 1, GL_FALSE, (float *)modelMatrix);
}

void setViewMatrix(mat4 viewMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(get_shader_program_id(), "viewMatrix"), 1, GL_FALSE, (float *)viewMatrix);
}

void setProjectionMatrix(mat4 projectionMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(get_shader_program_id(), "projectionMatrix"), 1, GL_FALSE, (float *)projectionMatrix);
}
