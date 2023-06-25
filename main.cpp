
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

using namespace std;

void framebuffer_size_cb(GLFWwindow *, int, int);
void processInput(GLFWwindow *);

static int WIDTH = 800;
static int HEIGHT = 600;

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "jaja", NULL, NULL);

  if (window == NULL) {
    cout << "Failed to load window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to init GLAD" << endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);

  while (!glfwWindowShouldClose(window)) {

    processInput(window);

    glClearColor(0.1f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_cb(GLFWwindow *window, int width, int height) {
  cout << "width " << width << " height " << height << endl;
  glViewport(0, 0, width, height);
}
