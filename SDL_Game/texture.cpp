#include "texture.h"
#include <iostream>
//#include <GL/glew.h>
//#include <SDL2/SDL_image.h>

int width;
int height;

Texture::Texture(){

}

Texture::Texture(char* file){

  texID = Texture::loadTextureFromFile(file);

}

Texture::Texture(GLuint id){

  texID = id;

}

Texture::~Texture(){

  glDeleteTextures(1, &texID);

}

GLuint Texture::loadTextureFromFile(char* file){

  GLuint id;

  SDL_Surface* texSurface = IMG_Load(file);

  if(texSurface == NULL){

      std::cerr << "FAILED IMAGE LOADING" << SDL_GetError() << std::endl;

  }

  glGenTextures(1, &id);

  glBindTexture(GL_TEXTURE_2D, id);

  int l1 = strlen(".jpg");
  int l2 = strlen(file);

  if(l1 < l2 && strcmp(&file[l2-l1], ".jpg") == 0 ){

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSurface->w, texSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texSurface->pixels);

  }else{

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texSurface->w, texSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texSurface->pixels);

  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  width = texSurface->w;

  height = texSurface->h;

  SDL_FreeSurface(texSurface);
    
  glBindTexture(GL_TEXTURE_2D, 0);

  return id;

}

void Texture::bind(){

  glBindTexture(GL_TEXTURE_2D, texID);

}

void Texture::unbind(){

  glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint Texture::getID(){

  return texID;

}

void Texture::setID(GLuint id){

  texID = id;

}

int Texture::getWidth(){

  return width;

}

int Texture::getHeight(){

  return height;

}
