
#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H

#include <glfw3.h>

// Struct is responsible for holding window properties
// It contains the width, height, title, and a pointer to the GLFW window
// The struct is used to pass window properties to the functions that create and manage the window
// The struct is also used to store the window properties for later use
// The struct is defined in the header file window_utils.h

typedef struct Window {
  int width;
  int height;
  const char* title;
  GLFWwindow* window;
} Window;

// Function to create a window with specified width, height, and title
// Returns a Window struct containing window properties
Window create_window_struct(int width, int height, const char* title);

// Function to center the window on the screen
// It retrieves the monitor information and calculates the position to center the window
void center_window(Window window);

#endif // WINDOW_UTILS_H
