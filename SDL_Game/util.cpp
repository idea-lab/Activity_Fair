#include "util.h"
#include <SDL2/SDL.h>
//#include <SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
//#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

SDL_Window *Util::win;
SDL_GLContext Util::sdlContext;

int Util::setup(int width, int height){

  if(SDL_Init(SDL_INIT_VIDEO) !=0){

        std::cout << "SDL_INIT_ERROR" << SDL_GetError() << std::endl;
        return 1;

    }

    win = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(win == NULL){

        std::cout << "SDL_CreateWidow ERROR" << SDL_GetError() << std::endl;

        SDL_Quit();

        return 1;

    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(ren == NULL){

        SDL_DestroyWindow(win);

        std::cout << "SD_CreateRenderer ERROR: " << SDL_GetError() << std::endl;

        SDL_Quit();

        return 1;

    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    sdlContext = SDL_GL_CreateContext(win);

    if(sdlContext == NULL){

        std::cerr << "COULD NOT CREATE OPENGL SDL CONTEXT" << std::endl;

        return 1;

    }

    glewExperimental = GL_TRUE;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLenum glewError = glewInit();

    if(glewError != GLEW_OK){

        std::cerr << "COULD NOT INITIALIZE GLEW" << std::endl;

        return 1;

    }
    return 0;
}

void Util::updateWindow(){

  SDL_GL_SwapWindow(win);

}

void Util::destroyWindow(){

  SDL_DestroyWindow(win);

}
