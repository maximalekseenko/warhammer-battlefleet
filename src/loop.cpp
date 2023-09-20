#include "loop.h"



#include "renderer.h"
#include "debug.h"
#include <SDL2/SDL_timer.h>


namespace loop
{
    bool isRunning=false;


    int Run()
    {
        loop::isRunning=true;
        
        while (isRunning)
        {
            Loop();
        }
    }


    int Loop()
    {
        renderer::Render();
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                isRunning = false;
                break;
            }
            SDL_Delay(1000 / 60);
        }
    }
}