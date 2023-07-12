
#include <string>
#define GLFW_INCLUDE_NONE
#include "../include/shader.h"
#include "../include/texture.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <iostream>

using namespace std;

void processInput(GLFWwindow *);
void framebuffer_size_cb(GLFWwindow *, int, int);

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

  Shader shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

  float vertices[] = {// pos              //color           //tex coords
                      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f};
  unsigned int indices[] = {0, 1, 2};
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // textures

  Texture texture1("assets/container.jpg", GL_TEXTURE0, GL_RGB);
  Texture texture2("assets/banana_block.png", GL_TEXTURE1, GL_RGBA);

  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  while (!glfwWindowShouldClose(window)) {

    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();
    glUniform1i(glGetUniformLocation(shaderProgram.id, "theTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram.id, "theTexture2"), 1);

    texture1.useTexture();
    texture2.useTexture();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
