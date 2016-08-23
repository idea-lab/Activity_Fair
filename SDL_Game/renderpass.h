#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <GL/glew.h>

#include "mesh.h"

class RenderPass{

  public:

    RenderPass();
    RenderPass(int numTextures, int width, int height);
    void setup(int amt, int width, int height, bool filtered);
    ~RenderPass();
    void begin();
    void end();
    void draw();
    GLuint *textures;
    
  private:
    
    GLuint frameBuffer;
    Mesh mesh;
    int numTextures;
    int w;
    int h;
    
};

#endif
