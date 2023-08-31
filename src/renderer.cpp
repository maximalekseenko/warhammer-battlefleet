#include "renderer.h"



#include <SDL.h>
#include "window.h"



namespace renderer
{
    SDL_Renderer* _renderer=NULL;
    bool isInited;


    int Init(int arg, const char** argv)
    {
        if (renderer::isInited) return false;

        // create renderer
        _renderer = SDL_CreateRenderer(window::window(), -1, SDL_RENDERER_ACCELERATED); 
        if (_renderer == NULL) return false;

        // return
        renderer::isInited = true;
        return true;
    }


    int Deinit()
    {
        if (!renderer::isInited) return false;

        // destroy renderer
        SDL_DestroyRenderer(_renderer); 

        // return
        renderer::isInited = false;
        return true;
    }


    SDL_Renderer* renderer() { return _renderer; }
}