#pragma once



#include <SDL2/SDL.h>



namespace renderer
{
    int Init(int arg, const char** argv);
    int Deinit();

    SDL_Renderer* renderer();
}