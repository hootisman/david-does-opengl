
#include <string>
#define GLFW_INCLUDE_NONE
#include "../include/shader.h"
#include "../include/texture.h"
#include "../include/block.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

void processInput(GLFWwindow *, float&, float&, float&);
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
  glEnable(GL_DEPTH_TEST);    //for depth buffer

  Shader shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

  // float vertices[] = {// pos              //color           //tex coords
  //                     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  //                     0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  //                     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
  //                     -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f};
  // unsigned int indices[] = {0, 1, 2, 0, 2, 3};
  // unsigned int VAO, VBO, EBO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EBO);

  // glBindVertexArray(VAO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
  //              GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
  //                       (void *)(6 * sizeof(float)));
  // glEnableVertexAttribArray(2);

  // textures

  Texture texture1("assets/container.jpg", GL_TEXTURE0, GL_RGB);
  Texture texture2("assets/awesomeface.png", GL_TEXTURE1, GL_RGBA);

  Block block1(0,0,0, texture1);
  Block block2(0,1.0f,0, texture1);

  float camX = 0.0f, camY = 0.0f, camZ = -3.0f;
  float TESTFOVANGLE = 45.0f;

  unsigned int VAO; 
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  BlockRenderer blockRenderer;

  blockRenderer.initBuffers();

  shaderProgram.use();
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    processInput(window, camX, camY, camZ);

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
      TESTFOVANGLE += 0.5f;
    }else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
      TESTFOVANGLE -= 0.5f;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //for depth buffer

    glUniform1i(glGetUniformLocation(shaderProgram.id, "theTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram.id, "theTexture2"), 1);


    texture1.useTexture();
    texture2.useTexture();
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(camX,camY,camZ));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(TESTFOVANGLE), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);



    glBindVertexArray(VAO);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "view"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.id, "projection"),1,GL_FALSE,glm::value_ptr(projection));

    block1.renderBlock(shaderProgram.id, blockRenderer);
    block2.renderBlock(shaderProgram.id, blockRenderer);


    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window, float& camX, float& camY, float& camZ) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    camZ += 0.1f;
  }else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    camX += 0.1f;
  }else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    camZ -= 0.1f;
  }else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    camX -= 0.1f;
  }else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
    camY -= 0.1f;
  }else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    camY += 0.1f;
  }
}

void framebuffer_size_cb(GLFWwindow *window, int width, int height) {
  cout << "width " << width << " height " << height << endl;
  glViewport(0, 0, width, height);
}
