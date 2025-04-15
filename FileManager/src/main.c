# include <stdio.h>
# include <glfw3.h>
# include <GL/gl.h>





int main(){

  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);
  glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
  glDepthFunc(GL_LESS); // Accept fragment if it closer to the camera than the former one
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
  glMatrixMode(GL_PROJECTION); // Set the projection matrix
  glMatrixMode(GL_MODELVIEW); // Set the modelview matrix
  glLoadIdentity(); // Load the identity matrix
  glTranslatef(0.0f, 0.0f, -5.0f); // Move the camera back

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Render here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    glBegin(GL_TRIANGLES); // Start drawing triangles
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glVertex3f(-1.0f, -1.0f, 0.0f); // First vertex
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
    glVertex3f(1.0f, -1.0f, 0.0f); // Second vertex
    glColor3f(0.0f, 0.0f, 1.0f); // Set color to blue
    glVertex3f(0.0f, 1.0f, 0.0f); // Third vertex
    glEnd(); // End drawing

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  printf("Hello, World!\n");
  return 0;
}