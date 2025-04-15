#include <glfw3.h>
#include <stdio.h>
#include <window_utils.h>

// Function is responsible for initializing GLFW
// Returns 0 on success, -1 on failure

int initialize_glfw() {
  if (!glfwInit()) {
      fprintf(stderr, "Failed to initialize GLFW\n");
      return -1;
  }
  return 0;
}


// Function is responsible for creating a window with the specified width, height, and title
// Returns a pointer to the created window, or NULL on failure

GLFWwindow* create_window(int width, int height, const char* title) {
  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
      fprintf(stderr, "Failed to create GLFW window\n");
      glfwTerminate();
      return NULL;
  }
  glfwMakeContextCurrent(window);
  return window;
}

// Function is responsible for setting up OpenGL settings
// Sets the depth test and clear color
// Sets the projection and modelview matrices

void setup_opengl() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
}
// Function is responsible for the main event loop
// It clears the screen, draws a triangle, and swaps buffers
// It also polls for events to handle user input and window events
// The loop continues until the window should close

void event_loop(GLFWwindow* window) {
  while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glBegin(GL_TRIANGLES);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glEnd();
      glfwSwapBuffers(window);
      glfwPollEvents();
  }
}