#ifndef UTIL_H
#define UTIL_H

#include <SDL2/SDL.h>

  class Util{

    

    public:

      static int setup(int width, int height);
      static void updateWindow();
      static void destroyWindow();
      static SDL_Window *win;
      static SDL_GLContext sdlContext;
    private:



  };

#endif
