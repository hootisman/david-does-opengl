#include "../include/block.h"
#include "../include/texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

BlockRenderer::BlockRenderer(float x, float y, float z){
    initBuffers();
    this->x = x;
    this->y = y;
    this->z = z;
    // texture1("assets/container.jpg", GL_TEXTURE0, GL_RGB);
    // texture2("assets/awesomeface.png", GL_TEXTURE1, GL_RGBA);
}
glm::mat4 BlockRenderer::getModel(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x,y,z));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f),glm::vec3(1.0f,0.5f,0.0f));

    return model;
}
void BlockRenderer::initBuffers(){

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

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void BlockRenderer::drawElements(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}