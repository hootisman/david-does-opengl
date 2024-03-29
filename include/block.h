#ifndef BLOCKRENDERER_H
#define BLOCKRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

const float vertices[] = {
    // pos              //color           //tex coords 
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//0 front bottom left
    -0.5f, 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,//1 front top left 
    0.5f,  -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//2 front bottom right
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,//3 front top right
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//4 back bottom left
    -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,//5 back top left
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//6 back bottom right
    0.5f,  0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f //7 back top right
    };
const int indices[] = {
    0,2,3,
    0,1,3,
    4,6,7,
    4,5,7,
    0,4,5,
    0,1,5,
    2,6,7,
    2,3,7,
    0,2,6,
    0,4,6,
    1,3,7,
    1,5,7
};
class BlockRenderer{
public:
    unsigned int VBO, EBO;

    glm::mat4 getModel(float, float, float);
    void draw();
    void initBuffers();
    void drawAllBlocks();
};

class Block{
private:
    const Texture& m_texture;

public:
    float x, y, z;

    Block(float, float, float, const Texture&);
    void renderBlock(unsigned int, BlockRenderer&); 
};

#endif