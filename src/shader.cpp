#include "../include/shader.h"
#include <filesystem>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragPath) {
  const char *vertexCode;
  const char *fragCode;
  std::string vCodeString, fCodeString;

  std::ifstream vertexFile, fragFile;

  vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    std::cout << vertexPath << " and " << fragPath << std::endl;
    std::cout << std::filesystem::current_path() << std::endl;
    vertexFile.open(vertexPath);
    fragFile.open(fragPath);

    std::stringstream vstream, fstream;
    vstream << vertexFile.rdbuf();
    fstream << fragFile.rdbuf();

    vertexFile.close();
    fragFile.close();
    vCodeString = vstream.str();
    fCodeString = fstream.str();

  } catch (std::ifstream::failure e) {
    std::cout
        << "ERROR READING SHADER FILE Shader::Shader(const char*, const char*) "
        << e.what() << std::endl;
  }

  vertexCode = vCodeString.c_str();
  fragCode = fCodeString.c_str();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexCode, NULL);
  glCompileShader(vertexShader);

  checkShaderCompilation(vertexShader, "VERTEX");

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragCode, NULL);
  glCompileShader(fragmentShader);

  checkShaderCompilation(fragmentShader, "FRAGMENT");

  id = glCreateProgram();

  glAttachShader(id, vertexShader);
  glAttachShader(id, fragmentShader);
  glLinkProgram(id);

  int success;
  char log[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, log);
    std::cout << "ERROR LINKING PROGRAM SHADERS\n" << log << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::checkShaderCompilation(unsigned int &shader, std::string name) {

  int success;
  char log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, log);
    std::cout << "ERROR COMPILING " << name << " SHADER\n" << log << std::endl;
  }
}
void Shader::use() { glUseProgram(id); }
