#ifndef GLFW_UTILS_H
#define GLFW_UTILS_H

#include <glfw3.h>

// Function to initialize GLFW
// Returns 0 on success, -1 on failure
int initialize_glfw();

// Function to create a window with specified width, height, and title
// Returns a pointer to the created window, or NULL on failure
GLFWwindow* create_window(int width, int height, const char* title);

// Function to set up OpenGL settings (depth test, clear color, matrices)
void setup_opengl();

// Function for the main event loop
// It will continue until the window should close
void event_loop(GLFWwindow* window);

#endif // GLFW_UTILS_H
