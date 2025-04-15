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
        glfwMakeContextCurrent(win.window);
    }
    
    return win;
}





