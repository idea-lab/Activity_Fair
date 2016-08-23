#include <iostream>
#include "renderpass.h"


  


RenderPass::RenderPass(){

  //setup(1, 640, 480);
    
    //REMOVED FUNCTIONALITY BECAUSE NOTHING USES THIS
    w = 0;
    h = 0;
}

RenderPass::RenderPass(int amt, int width, int height){

  //setup(amt,width, height);
    w = 0;
    h = 0;
}

RenderPass::~RenderPass(){

  glDeleteBuffers(1, &frameBuffer);
  glDeleteTextures(numTextures, &textures[0]);

}

void RenderPass::setup(int amt, int width, int height, bool filtered){
    
    std::cout << width << std::endl;
    
    w = width;
    h = height;
    
    
    static GLfloat vertPositions[] = {

    -1.0,-1.0,-1.0,
    0.0,0.0,

    1.0,-1.0,-1.0,
    1.0,0.0,

    1.0,1.0,-1.0,
    1.0,1.0,

    1.0,1.0,-1.0,
    1.0,1.0,

    -1.0,1.0,-1.0,
    0.0,1.0,

    -1.0,-1.0,-1.0,
    0.0,0.0

    };

    mesh.setVerts(vertPositions, sizeof(vertPositions)/sizeof(GLfloat));
    
  if(!GL_EXT_framebuffer_object){

    std::cerr << "FRAMEBUFFER OBJECT NOT SUPPORTED :(" << std::endl;

  }

  if(amt <= 0){

    std::cerr << "CANNOT HAVE " << amt << " TEXTURES STORED IN FRAMEBUFFER. DEFAULTING TO 1" << std::endl;
    amt = 1;

  }

  textures = new GLuint[amt];

    numTextures = amt;
    
  glGenTextures(amt, &textures[0]);

  glGenFramebuffers(1, &frameBuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

  GLenum DrawBuffers[amt];

  for(int i = 0; i < amt; i++){

  glBindTexture(GL_TEXTURE_2D, textures[i]);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

if(filtered){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
}else{
      
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
}
      
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+i,GL_TEXTURE_2D, textures[i], 0);

  DrawBuffers[i] = GL_COLOR_ATTACHMENT0+i;
  std::cout << textures[i] << std::endl;
  }

  glDrawBuffers(amt, DrawBuffers);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {

    std::cerr << "PROBLEM MAKING FBO:" << std::endl;

    GLint fboProblem = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch(fboProblem){

      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cerr<< "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;

      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cerr<< "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;

      case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cerr<< "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << std::endl;

      case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cerr<< "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << std::endl;
      case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cerr<< "GL_FRAMEBUFFER_UNSUPPORTED" << std::endl;

    }

  }
  else
  {

    std::cout<< "GL_FRAMEBUFFER_COMPLETE" << std::endl;

  }


  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glBindTexture(GL_TEXTURE_2D, 0);

}

void RenderPass::begin(){

  glViewport(0,0,w,h);
  glBindTexture(GL_TEXTURE_2D,0);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glClear(GL_COLOR_BUFFER_BIT);

}

void RenderPass::end(){

  glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

}

void RenderPass::draw(){
    //glBindTexture(GL_TEXTURE_2D, textures[index]);

    mesh.draw();
    
  /*   glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
//                               vboid is 1
  glBindBuffer(GL_ARRAY_BUFFER, 1);
  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5*4, 0);
  glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5*4, (const GLvoid*)12);

  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableClientState(GL_VERTEX_ARRAY);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
    */
    //FIX THIS BUG PLEASE I WANT TO KILL MYSELF EVERY TIME I LOOK AT THIS STUPID WORKAROUND 
    
}
