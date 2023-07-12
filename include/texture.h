#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
  unsigned int id;
  int width;
  int height;
  int nrChannels;
  GLenum textureUnit;

  Texture(const char *, GLenum, GLenum);
  void useTexture();
};

#endif
