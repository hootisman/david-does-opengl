
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

using namespace std;

void newShaderProgram(unsigned int &);
void checkShaderCompilation(unsigned int &, string);
void processInput(GLFWwindow *);
void framebuffer_size_cb(GLFWwindow *, int, int);

static int WIDTH = 800;
static int HEIGHT = 600;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                   "}\n\0";

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

  unsigned int shaderProgram;
  newShaderProgram(shaderProgram);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {

    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
void newShaderProgram(unsigned int &shaderProgram) {

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  checkShaderCompilation(vertexShader, "VERTEX");

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  checkShaderCompilation(fragmentShader, "FRAGMENT");

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char log[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, log);
    cout << "ERROR LINKING PROGRAM SHADERS\n" << log << endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void checkShaderCompilation(unsigned int &shader, string name) {

  int success;
  char log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, log);
    cout << "ERROR COMPILING " << name << " SHADER\n" << log << endl;
  }
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
