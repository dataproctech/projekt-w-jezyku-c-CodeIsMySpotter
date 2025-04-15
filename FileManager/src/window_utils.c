#include <stdio.h>
#include <glfw3.h>
#include <GL/gl.h>
#include "window_utils.h"
#include "glfw_utils.h"

// Function prototypes
int initialize_glfw();
GLFWwindow* create_window(int width, int height, const char* title);
void setup_opengl();
void event_loop(GLFWwindow* window);




// Function is responsible for creating a window with the specified width, height, and title
// It returns a Window struct containing the window properties
// The function initializes the GLFW library and creates a window with the specified properties
// The function also sets the context for the window and returns a pointer to the created window

Window create_window_struct(int width, int height, const char* title) {
    Window win;
    win.width = width;
    win.height = height;
    win.title = title;
    win.window = create_window(width, height, title);

    if (!win.window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        win.width = 0;
        win.height = 0;
        win.title = NULL;
        win.window = NULL;
    } else {
      center_window(win);
      glfwMakeContextCurrent(win.window);
    }

    return win;
}


// Function is responsible for centering the window on the screen
// It retrieves the monitor information and calculates the position to center the window
// The function uses the GLFW library to get the monitor information and set the window position
// The function takes a Window struct as an argument and sets the window position based on the monitor resolution

void center_window(Window window){
    int monitor_count;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    if (monitor_count > 0) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitors[0]);
        int x = (mode->width - window.width) / 2;
        int y = (mode->height - window.height) / 2;
        glfwSetWindowPos(window.window, x, y);
    }
    else {
        fprintf(stderr, "No monitors found\n");
    }
}





