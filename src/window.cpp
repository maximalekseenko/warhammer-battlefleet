#include "window.h"



#include <SDL.h>



namespace window
{
    SDL_Window* _window=NULL;
    bool isInited;


    int Init(int arg, const char** argv)
    {
        if (window::isInited) return false;

        // create window
        _window = SDL_CreateWindow("warhammer:battlefleet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0); 
        if (_window == NULL) return false;

        // return
        window::isInited = true;
        return true;
    }


    int Deinit()
    {
        if (!window::isInited) return false;

        // destroy window
        SDL_DestroyWindow(_window); 

        // return
        window::isInited = false;
        return true;
    }


    SDL_Window* window() { return _window; }
}
