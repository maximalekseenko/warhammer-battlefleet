#include "init.h"



#include "window.h"
#include "renderer.h"
#include "debug.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>



namespace init
{
    int Init(int arg, const char** argv)
    {
        SDL_Init(SDL_INIT_TIMER);
        TTF_Init();
        debug::Init(arg, argv);
        window::Init(arg, argv);
        renderer::Init(arg, argv);
    }


    int Deinit()
    {
        debug::Deinit();
        window::Deinit();
        renderer::Deinit();
        SDL_Quit();
        TTF_Quit();
    }
}