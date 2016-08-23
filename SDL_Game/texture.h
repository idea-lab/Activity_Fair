#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL2/SDL_image.h>

class Texture{

  public:

    Texture();
    Texture(char* file);
    Texture(GLuint id);
    ~Texture();
    GLuint getID();
    void setID(GLuint id);
    int getWidth();
    int getHeight();
    GLuint loadTextureFromFile(char* file);
    void bind();
    void unbind();

  private:

    GLuint texID;
    int width;
    int height;

};

#endif
