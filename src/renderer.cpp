#include "renderer.h"



#include "window.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "debug.h"
#include <string>


namespace renderer
{
    SDL_Renderer* _renderer=NULL;
    bool isInited;
    TTF_Font* Sans;



    int Init(int arg, const char** argv)
    {
        if (renderer::isInited) return false;
        renderer::Sans = TTF_OpenFont("./data/font/oldenglishtextmt.ttf", 24);

        // create renderer
        renderer::_renderer = SDL_CreateRenderer(window::window(), -1, SDL_RENDERER_ACCELERATED); 
        if (renderer::_renderer == NULL) return false;

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


    void Render()
    {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "In His name\nAnd by\nHis word", {0xff,0xff,0xff});
        SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

        SDL_Rect Message_rect {
            .x = 0,
            .y = 0,
            .w = surfaceMessage->w,
            .h = surfaceMessage->h,
        };
        SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);

        SDL_RenderPresent(_renderer);
    }
}