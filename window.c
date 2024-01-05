#include <stdlib.h>
#include <stdio.h>
#include "window.h"

static GLFWwindow* window = NULL;
static unsigned int isDebug = 0;

vec3 direction = {};

float mouseX = -90.0f;

float lastMouseX = 480.0f; // x center
float lastMouseY = 270.0f; // y center

int firstMouse = 1;

void init_window()
{
    isArrowKeyUp = 0;
    isArrowKeyDown = 0;
    isArrowKeyLeft = 0;
    isArrowKeyRight = 0;

    glfwSetErrorCallback(on_error);

    if(!glfwInit())
    {
        printf("Cannot initialize GLFW...\n");
    }

    // OpenGL Version & context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Learn OpenGL - 3D", NULL, NULL);

    if(!window)
    {
        printf("Cannot intialize window...\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("GLAD INIT FAILED\n");
    }

    glfwSetFramebufferSizeCallback(window, on_framebuffer_update);
    glfwSetKeyCallback(window, on_key_changes);
    glfwSetScrollCallback(window, on_mouse_scroll_changes);
    glfwSetCursorPosCallback(window, on_mouse_cursor_changes);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void on_key_changes(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        isDebug = !isDebug;
    }

    isArrowKeyUp = key == GLFW_KEY_UP && action == GLFW_PRESS;
    isArrowKeyDown = key == GLFW_KEY_DOWN && action == GLFW_PRESS;
    isArrowKeyLeft = key == GLFW_KEY_LEFT && action == GLFW_PRESS;
    isArrowKeyRight = key == GLFW_KEY_RIGHT && action == GLFW_PRESS;

}

void on_framebuffer_update(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void on_mouse_cursor_changes(GLFWwindow* window, double xPos, double yPos)
{
    if(firstMouse)
    {
        lastMouseX = xPos;
        lastMouseY = yPos;
        firstMouse = 0;
    }

    float offsetX = xPos - lastMouseX;
    float offsetY = lastMouseY - yPos;

    lastMouseX = xPos;
    lastMouseY = yPos;

    const float sensitivity = 0.1f;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    mouseX += offsetX;
    mouseY += offsetY;

    if(mouseY > 89.0f) // prevent the camera to be upside down
    {
        mouseY = 89.0f;
    }
    if(mouseY < -89.0f)
    {
        mouseY = -89.0f;
    }
}

void on_mouse_scroll_changes(GLFWwindow* window, double xOffset, double yOffset)
{
}

void on_error(int errorCode, const char* description)
{
    printf("\n------------\nERROR : %d : %s\n", errorCode, description);
}

GLFWwindow* get_window()
{
    return window;
}

unsigned int is_debug()
{
    return isDebug;
}
