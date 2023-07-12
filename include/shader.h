#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader{
    public:
        unsigned int id;
        Shader(const char* vertexPath, const char* fragPath);
        void checkShaderCompilation(unsigned int& shader, std::string name);
        void use();

};
#endif