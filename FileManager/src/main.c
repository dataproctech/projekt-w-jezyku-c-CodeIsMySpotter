#include <stdio.h>
#include <glfw3.h>
#include <GL/gl.h>
// Update the path to the correct location of window_utils.h
#include "window_utils.h"
#include "glfw_utils.h"



// Main function is the entry point of the program
// It initializes GLFW, creates a window, sets up OpenGL, and enters the event loop
// Finally, it cleans up and terminates GLFW
// Returns 0 on success, -1 on failure

int main() {
    if (initialize_glfw() != 0) {
        return -1;
    }

    Window window = create_window_struct(1000, 600, "Hello World");
    if (!window.window) {
        return -1;
    }

    setup_opengl();
    event_loop(window.window);

    printf("Hello, World!\n");
    glfwDestroyWindow(window.window);
    glfwTerminate();
    return 0;
}
