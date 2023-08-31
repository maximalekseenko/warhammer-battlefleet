#pragma once



#include <SDL2/SDL.h>



namespace window
{
    int Init(int arg, const char** argv);
    int Deinit();

    SDL_Window* window();
}
