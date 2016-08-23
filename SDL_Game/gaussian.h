#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include <iostream>
#include <GL/glew.h>
#include "renderpass.h"
#include "shader.h"
class Gaussian{

  public:

    Gaussian(int width, int height);
    ~Gaussian();
    void begin();
    void end();
    GLuint getTexture();
  private:
    void setup(int width, int height);
    RenderPass pass1;
    RenderPass pass2;
    Shader hShader;
    Shader vShader;

};

#endif