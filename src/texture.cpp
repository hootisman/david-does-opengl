#include "../include/texture.h"
#include "../include/stb_image.h"

Texture::Texture(const char *imagePath, GLenum textureUnit, GLenum format) {
  unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

  glGenTextures(1, &id);

  this->textureUnit = textureUnit;
  glActiveTexture(this->textureUnit);

  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::useTexture() {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, id);
}
