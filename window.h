#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>

#define WIN_WIDTH 960
#define WIN_HEIGHT 540

unsigned int isArrowKeyUp;
unsigned int isArrowKeyDown;
unsigned int isArrowKeyLeft;
unsigned int isArrowKeyRight;

float mouseX;
float mouseY;

void init_window();

void on_key_changes(GLFWwindow* window, int key, int scancode, int action, int mods);

void on_mouse_cursor_changes(GLFWwindow* window, double xPos, double yPos);

void on_mouse_scroll_changes(GLFWwindow* window, double xOffset, double yOffset);

void on_framebuffer_update(GLFWwindow* window, int width, int height);

void on_error(int errorCode, const char* description);

GLFWwindow* get_window();

unsigned int is_debug();

#endif // WINDOW_H_INCLUDED
