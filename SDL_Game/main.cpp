#include <SDL2/SDL.h>
//#include <SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
//#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glew.h>
#include <math.h>

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <ctime>
#include <functional>
    
#include "shader.h"
#include "mesh.h"
#include "renderpass.h"
#include "util.h"
#include "texture.h"
#include "gaussian.h"

SDL_Event event;




GLfloat vertPositions[] = {

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

GLfloat healthBarPositions[] = {

    0.0,-1.0,-1.0,
    0.0,0.0,

    1.0,-1.0,-1.0,
    1.0,0.0,

    1.0,1.0,-1.0,
    1.0,1.0,

    1.0,1.0,-1.0,
    1.0,1.0,

    0.0,1.0,-1.0,
    0.0,1.0,

    0.0,-1.0,-1.0,
    0.0,0.0

};

GLuint ctex;
GLuint ntex;

GLuint FBO;
GLuint FBOTex;

glm::mat4 redHealthTrans;
glm::mat4 blueHealthTrans;

const float width = 1280;
const float height = 720;

float p1x; //position x
float p1y; //position y

float p1vx; //velocity x
float p1vy; //velocity y

const float p1a = 0.02f; //acceleration constant
const float p1d = 0.97f; //deceleration constant (multiplicative)

float p1r; //rotation 0 to 2pi

float p2x;
float p2y;

float p2vx;
float p2vy;

int firetime1;
int firetime2;

const float p2a = 0.02f; 
const float p2d = 0.97f;

int p1health;
int p2health;


float p2r;

const double TWOPI = 2 * M_PI;

bool up_key, down_key, left_key, right_key, w_key, a_key, s_key, d_key;

const Uint8 *keystate = SDL_GetKeyboardState(NULL);;

struct bullet{
    
    float x;
    float y;
    float dx;
    float dy;
    bool isactive;
};

struct bullet bullets1[5];
struct bullet bullets2[5];


float distance(float x1, float y1, float x2, float y2){
    
    float a = x2-x1;
    float b = y2-y1;
    //std::cout <<sqrt(a*a + b*b) << std::endl;
    return sqrt(a*a + b*b);
    
}

void doPhysics(){
    
    if(keystate[SDL_GetScancodeFromKey(SDLK_UP)]){
        
        p1vx += p1a * -sin(p1r);
        p1vy += p1a * cos(p1r);
        
    }else{
        
        p1vx *= p1d;
        p1vy *= p1d;
        
    }

    if(keystate[SDL_GetScancodeFromKey(SDLK_LEFT)]){
        
        p1r += 0.15;
        
        if(p1r >= TWOPI){
            p1r -= TWOPI;
        }
        if(p1r < 0){
            p1r += TWOPI;
        }
        
    }

    if(keystate[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        
        p1r -= 0.15;
        
        if(p1r >= TWOPI){
            p1r -= TWOPI;
        }
        if(p1r < 0){
            p1r += TWOPI;
        }
        
    }

    p1x += p1vx;
    p1y += p1vy;
    
    if(p1x < -25.0f){
        p1x = -25.0f;
        p1vx *= -1;
    }
    if(p1x > 25.0f){
        p1x = 25.0f;
        p1vx *= -1;
    }
    if(p1y < -15.0f){
        p1y = -15.0f;
        p1vy *= -1;
    }
    if(p1y > 15.0f){
        p1y = 15.0f;
        p1vy *= -1;
    }
    
    if(keystate[SDL_GetScancodeFromKey(SDLK_w)]){
        
        p2vx += p2a * -sin(p2r);
        p2vy += p2a * cos(p2r);
        
    }else{
        
        p2vx *= p2d;
        p2vy *= p2d;
        
    }

    if(keystate[SDL_GetScancodeFromKey(SDLK_a)]){
        
        p2r += 0.15;
        
        if(p2r >= TWOPI){
            p2r -= TWOPI;
        }
        if(p2r < 0){
            p2r += TWOPI;
        }
        
    }
    
    if(keystate[SDL_GetScancodeFromKey(SDLK_d)]){
        
        p2r -= 0.15;
        
        if(p2r >= TWOPI){
            p2r -= TWOPI;
        }
        if(p2r < 0){
            p2r += TWOPI;
        }
        
    }
    
    p2x += p2vx;
    p2y += p2vy;
    
    if(p2x < -25.0f){
        p2x = -25.0f;
        p2vx *= -1;
    }
    if(p2x > 25.0f){
        p2x = 25.0f;
        p2vx *= -1;
    }
    if(p2y > 15.0f){
        p2y = 15.0f;
        p2vy *= -1;
    }
    if(p2y < -15.0f){
        p2y = -15.0f;
        p2vy *= -1;
    }
    
    if(keystate[SDL_GetScancodeFromKey(SDLK_DOWN)]){
        if(firetime1 > 10 || firetime1 == 0){
            for(int i = 0; i < 5; i++){
            
                if(!bullets1[i].isactive){
                //std::cout <<"mepp" <<std::endl;
                    bullets1[i].isactive = true;
                    
                    bullets1[i].x = p1x;
                    bullets1[i].y = p1y;
                
                    bullets1[i].dx = 1.0 * -sin(p1r);
                    bullets1[i].dy = 1.0 * cos(p1r);
                
                    firetime1 = 1;
                
                    break;
                }
            }

        }
    }
    
    if(keystate[SDL_GetScancodeFromKey(SDLK_s)]){
        if(firetime2 > 10 || firetime2 == 0){
            for(int i = 0; i < 5; i++){
            
                if(!bullets2[i].isactive){
                //std::cout <<"mepp" <<std::endl;
                    bullets2[i].isactive = true;
                    
                    bullets2[i].x = p2x;
                    bullets2[i].y = p2y;
                
                    bullets2[i].dx = 1.0 * -sin(p2r);
                    bullets2[i].dy = 1.0 * cos(p2r);
                
                    firetime2 = 1;
                
                    break;
                }
            }

        }
    }
    
    for(int i = 0; i < 5; i++){
        
        if(bullets1[i].isactive){

            bullets1[i].x += bullets1[i].dx;
            bullets1[i].y += bullets1[i].dy;
        
        
            if(bullets1[i].x <-25.0f ||bullets1[i].x >25.0f ||bullets1[i].y <-25.0f ||bullets1[i].y >25.0f){
            
                bullets1[i].x = 0;
                bullets1[i].y = 0;
                bullets1[i].dx = 0;
                bullets1[i].dy = 0;
                bullets1[i].isactive = false;
            
            }
        
            //if(abs(p2x - bullets1[i].x) < 1.0f && abs(p2y - bullets1[i].y) < 1.0){
            
            if(distance(bullets1[i].x, bullets1[i].y, p2x, p2y) <= 1.8f){
            
                //HIT
            
                bullets1[i].x = 0;
                bullets1[i].y = 0;
                bullets1[i].dx = 0;
                bullets1[i].dy = 0;
                bullets1[i].isactive = false;
                if(p2health == 1){
                p2x = -10;
                p2y = 0;
                p2vx = 0;
                p2vy = 0;
                p2r = 3*TWOPI/4.0f;
                p2health = 25;
                }else{
                    p2health -= 1;
                }
                redHealthTrans = glm::scale(glm::rotate(glm::translate(glm::vec3(0.0f,13.0f,0.0f)),3.14f,glm::vec3(0.0f,0.0f, 1.0f)),glm::vec3(p2health,1.0f,1.0f));
            }
            
        }
        
    }
    
    for(int i = 0; i < 5; i++){
        
        if(bullets2[i].isactive){
            
            bullets2[i].x += bullets2[i].dx;
            bullets2[i].y += bullets2[i].dy;
        
        
            if(bullets2[i].x < -25.0f ||bullets2[i].x > 25.0f ||bullets2[i].y < -25.0f ||bullets2[i].y > 25.0f){
            
                bullets2[i].x = 0;
                bullets2[i].y = 0;
                bullets2[i].dx = 0;
                bullets2[i].dy = 0;
                bullets2[i].isactive = false;
            
            }
        
           // if(abs(p1x - bullets2[i].x) < 1.0f && abs(p1y - bullets2[i].y) < 1.0){
             if(distance(bullets2[i].x, bullets2[i].y, p1x, p1y) <= 1.8f){
                //HIT
            
                bullets2[i].x = 0;
                bullets2[i].y = 0;
                bullets2[i].dx = 0;
                bullets2[i].dy = 0;
                bullets2[i].isactive = false;
                if(p1health == 1){
                p1x = 10;
                p1y = 0;
                p1vx = 0;
                p1vy = 0;
                p1r = TWOPI/4.0f;
                p1health = 25;
                }else{
                    p1health -= 1;
                }
                blueHealthTrans = glm::scale(glm::rotate(glm::translate(glm::vec3(0.0f,13.0f,0.0f)),0.0f,glm::vec3(0.0f,0.0f, 1.0f)),glm::vec3(p1health,1.0f,1.0f));
            }
            
        }
        
    }
    if(firetime1 != 0) firetime1++;
    if(firetime2 != 0) firetime2++;
}

int main(int argc, char** argv)
{

    p1health = 25;
    p2health = 25;
    
    Util::setup(width, height);

    
    //bullets1 = new bullet[5];
    //bullets2 = new bullet[5];
    
    //keystate = SDL_GetKeyboardState(NULL);
    Mesh mesh = Mesh();
    mesh.setVerts(vertPositions, sizeof(vertPositions) / sizeof(GLfloat));
    //Mesh p2 = Mesh(vertPositions);

    Mesh healthBar = Mesh();
    healthBar.setVerts(healthBarPositions, sizeof(vertPositions) / sizeof(GLfloat));
    
    Shader entityShader = Shader("shaders/entity");
    Shader postShader = Shader("shaders/post");


    glm::mat4 projection = glm::ortho(-25.0f, 25.0f, -25.0f*(height/width), 25.0f*(height/width), 0.0f, 1.0f);
    glm::mat4 vp = projection;
    
    glm::mat4 transform1 = glm::translate(glm::vec3(0.0f,0.0f,0.0f)) * glm::rotate(p1r,glm::vec3(p1x,p1y, 0.0f));
    
    glm::mat4 transform2 = glm::translate(glm::vec3(0.0f,0.0f,0.0f)) * glm::rotate(p1r,glm::vec3(p1x,p1y, 0.0f));
    
    glm::mat4 bulletTransform = glm::translate(glm::vec3(0.0f,0.0f,0.0f));
    
    GLuint vpLoc = glGetUniformLocation(entityShader.getID(), "vp");
    GLuint transformLoc = glGetUniformLocation(entityShader.getID(), "transform");

    redHealthTrans = glm::scale(glm::rotate(glm::translate(glm::vec3(0.0f,13.0f,0.0f)),3.14f,glm::vec3(0.0f,0.0f, 1.0f)),glm::vec3(25.0f,1.0f,1.0f));
    
    blueHealthTrans = glm::scale(glm::rotate(glm::translate(glm::vec3(0.0f,13.0f,0.0f)),0.0f,glm::vec3(0.0f,0.0f, 1.0f)),glm::vec3(25.0f,1.0f,1.0f));

    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    
    Texture triangle_tex = Texture("res/img/ship_sprite.png");
    Texture circle_tex = Texture("res/img/circle_sprite.png");
    Texture square_tex = Texture("res/img/square.png");
    
    GLuint imgLoc = glGetUniformLocation(entityShader.getID(),"tex");
    GLuint colorLoc = glGetUniformLocation(entityShader.getID(),"color");
    GLuint glowColorLoc = glGetUniformLocation(entityShader.getID(),"glowColor");
    
    GLuint rpColorLoc = glGetUniformLocation(postShader.getID(),"rpColor");
    GLuint rpBlurLoc = glGetUniformLocation(postShader.getID(),"rpBlur");
    
    RenderPass rp = RenderPass();
    rp.setup(2, width, height, false);
    //rp.setup(2, 320, 240);
    bool quit = false;
    double phase = 0.00;

    glClearColor(0.0, 0.0, 0.0, 0.0);

    std::cout << "begin" << std::endl;
    
    Gaussian gauss = Gaussian(width,height);
    
    std::cout << "end" << std::endl;

    int ms;
    
    std::clock_t start;
    
    while (!quit) {
        
        start = std::clock();
        
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_EXPOSED:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        if (phase > TWOPI) {
            phase -= TWOPI;
        }

        phase += M_PI / 100;

        doPhysics();
        
        transform1 = glm::rotate(glm::translate(glm::vec3(p1x,p1y,0.0f)),p1r,glm::vec3(0.0f,0.0f, 1.0f));
    
        transform2 = glm::rotate(glm::translate(glm::vec3(p2x,p2y,0.0f)),p2r,glm::vec3(0.0f,0.0f, 1.0f));
        
       // transform = glm::rotate(glm::translate(glm::vec3(p1x,p1y,0.0f)),p1r,glm::vec3(0.0f,0.0f, 1.0f)) *;
        
        //glClearColor(0.5, cos(phase) / 2 + .5, 0.5, 0.0);

        glClear(GL_COLOR_BUFFER_BIT);

        rp.begin();
        //gauss.begin();
        entityShader.bind();

        glUniform1i(imgLoc,0);

        glUniformMatrix4fv(vpLoc,1,GL_FALSE,&vp[0][0]);
        
        glActiveTexture(GL_TEXTURE0);
        triangle_tex.bind();

        glUniformMatrix4fv(transformLoc,1,GL_FALSE,&transform1[0][0]);
        
        glUniform3f(colorLoc, 0.7f, 0.7f, 1.0f);
        glUniform3f(glowColorLoc, 0.0f, 0.0f, 1.0f);
        
        //glUniform2f(motionLoc, p1vx, p1vy);
        
        mesh.draw();

        //entityShader.unbind();
        
        /////////////////////////////////////////
        
        //entityShader.bind();
        
        
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,&transform2[0][0]);
        
        glUniform3f(colorLoc, 1.0f, 0.7f, 0.7f);
        glUniform3f(glowColorLoc, 1.0f, 0.0f, 0.0f);
        
        //glUniform2f(motionLoc, p2vx, p2vy);
        
        mesh.draw();
        
        glUniform3f(colorLoc, 0.7f, 0.7f, 1.0f);
        glUniform3f(glowColorLoc, 0.0f, 0.0f, 1.0f);
        
        circle_tex.bind();
        
        for(int i = 0; i < 5; i++){
            if(bullets1[i].isactive){
                
                bulletTransform = glm::translate(glm::vec3(bullets1[i].x,bullets1[i].y,0.0f));
                
                glUniformMatrix4fv(transformLoc,1,GL_FALSE,&bulletTransform[0][0]);
                
                //glUniform2f(motionLoc, bullets1[i].dx,bullets1[i].dy);

                
                mesh.draw();
                
            }
            
        }
        
        glUniform3f(colorLoc, 1.0f, 0.7f, 0.7f);
        glUniform3f(glowColorLoc, 1.0f, 0.0f, 0.0f);
        
        circle_tex.bind();
        
        for(int i = 0; i < 5; i++){
            if(bullets2[i].isactive){
                
                bulletTransform = glm::translate(glm::vec3(bullets2[i].x,bullets2[i].y,0.0f));
                
                glUniformMatrix4fv(transformLoc,1,GL_FALSE,&bulletTransform[0][0]);
                
                //glUniform2f(motionLoc, bullets1[i].dx,bullets1[i].dy);

                mesh.draw();
                
            }
            
        }
        
        square_tex.bind();
        
        glUniform3f(colorLoc, 1.0f, 0.7f, 0.7f);
        glUniform3f(glowColorLoc, 1.0f, 0.0f, 0.0f);
        
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,&redHealthTrans[0][0]);
                
        healthBar.draw();
        
        glUniform3f(colorLoc, 0.7f, 0.7f, 1.0f);
        glUniform3f(glowColorLoc, 0.0f, 0.0f, 1.0f);
        
        glUniformMatrix4fv(transformLoc,1,GL_FALSE,&blueHealthTrans[0][0]);
                
        healthBar.draw();
        
        entityShader.unbind();
        
        rp.end();
        //gauss.end();
        glClear(GL_COLOR_BUFFER_BIT);
        
        //////////
        
        gauss.begin();

        glBindTexture(GL_TEXTURE_2D, rp.textures[1]);
        
        //mesh.draw();
        rp.draw();
        
        gauss.end();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        ////////
        glViewport(0,0,width,height);
        postShader.bind();
        //gauss.begin();
        
        //gauss.begin();
        glUniform1i(rpColorLoc,0);
        glUniform1i(rpBlurLoc,1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rp.textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gauss.getTexture());
        //glBindTexture(GL_TEXTURE_2D, 6);
        
        //mesh.draw();
        
        rp.draw();
       // gauss.begin();
        //gauss.end();
        //postShader.unbind(); 
        //gauss.end();

        Util::updateWindow();
        ms = (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000);
        SDL_Delay(33 - ms);
    }

    glDeleteBuffers(1, &FBO);
    glDeleteTextures(1, &ctex);
    glDeleteTextures(1, &FBOTex);
    Util::destroyWindow();
    return 0;
}
