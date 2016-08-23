#include "gaussian.h"



Gaussian::Gaussian(int width, int height){
    
    setup(width, height);
    
}

Gaussian::~Gaussian(){
    
}

void Gaussian::begin(){
   // pass2.draw();
    //std::cout << "gauss" << std::endl;
    pass1.begin();
    glClear(GL_COLOR_BUFFER_BIT);
    hShader.bind();
    
    glActiveTexture(GL_TEXTURE0);
    

}

//NOT DOING UNIFORMS FOR THESE BECAUSE OpenGL DEFAULTS THE SAMPLER TO 0

void Gaussian::end(){
    
    hShader.unbind();

    pass1.end();
    
    //2nd pass starts here
    
    pass2.begin();
    //glClear(GL_COLOR_BUFFER_BIT);
    vShader.bind();
    
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_2D, pass1.textures[0]);
    
    pass1.draw();
    
    vShader.unbind();

    pass2.end();
}

GLuint Gaussian::getTexture(){
    
    return pass2.textures[0];
    
}

void Gaussian::setup(int width, int height){
    std::cout << "pass1" << std::endl;
    pass1.setup(1,width/2,height/2, true); //DOWNSCALE FOR BETTER PERFORMANCE & MORE BLUR
    std::cout << "pass2" << std::endl;
    pass2.setup(1,width/2,height/2, true); //DOWNSCALE FOR BETTER PERFORMANCE & MORE BLUR
    
    
    hShader = Shader("shaders/hgauss");
    vShader = Shader("shaders/vgauss");
    

}