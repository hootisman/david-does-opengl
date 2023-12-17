
#include "../include/texture.h"
#include "../include/block.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

// Block::Block(float x, float y, float z, const Texture& texture){
//     this->x = x;
//     this->y = y;
//     this->z = z;
// }
Block::Block(float x, float y, float z, const Texture& texture) : m_texture(texture) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Block::renderBlock(unsigned int shaderId, BlockRenderer& renderer){
    glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"),1,GL_FALSE,glm::value_ptr(renderer.getModel(this->x, this->y, this->z)));
    renderer.draw();
}

glm::mat4 BlockRenderer::getModel(float x, float y, float z){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f),glm::vec3(1.0f,0.5f,0.0f));

    return model;
}
void BlockRenderer::initBuffers(){

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

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
void BlockRenderer::draw(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
