#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include "../common/data/imerial.h"
#include "../common/objects/vessel.h"
#include "../common/mechanic/movement.h"
#include <iostream>


#define RAD_TO_DEG(x) ((x) * (180.0f / M_PI))
#define DEG_TO_RAD(x) ((x) / (180.0f / M_PI))

#define IMAGEDOWNSCALE 6


void DrawCircle(
            SDL_Renderer* renderer, 
            int32_t centreX, 
            int32_t centreY, 
            int32_t radius,
            Uint64 color
            )
{

    SDL_SetRenderDrawColor(
        renderer, 
        (color & 0xff0000) / 0x00ffff, 
        (color & 0x00ff00) / 0x0000ff, 
        (color & 0x0000ff), 
        255);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);


        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}


SDL_Texture* LoadTexture(const char* __path, SDL_Renderer* __rend)
{
    // creates a surface to load an image into the main memory
    SDL_Surface* _surface;
 
    // please provide a path for your image
    _surface = IMG_Load(__path);
 
    // loads image to our graphics hardware memory.
    SDL_Texture* _texture = SDL_CreateTextureFromSurface(__rend, _surface);
 
    // clears main-memory
    SDL_FreeSurface(_surface);

    return _texture;
}
 

int main(int argc, char *argv[])
{
    Vessel v1{ .vesselType=&ImperialVesselTypeCruiser };

    v1.CurrentState.position[0] = 300;
    v1.CurrentState.position[1] = 300;
    v1.CurrentState.rotation = M_PI_4;
 
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    SDL_Texture* tex = LoadTexture(v1.vesselType->IMAGE_PATH, rend);
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);


    SDL_Texture* mark = LoadTexture("mark.png", rend);
    SDL_Rect mark_dest;
    SDL_QueryTexture(mark, NULL, NULL, &mark_dest.w, &mark_dest.h);

 
    // adjust height and width of our image box.
    dest.w /= IMAGEDOWNSCALE;
    dest.h /= IMAGEDOWNSCALE;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 300;
 
    // animation loop
    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_MOUSEMOTION:
                // dest.x = event.motion.x;
                // dest.y = event.motion.y;
                SetStates(&v1, event.motion.x, event.motion.y, 3);

                break;
            }
        }

        // clears the screen
        SDL_SetRenderDrawColor(rend, 0x55, 0x55, 0x55, 0x55);
        SDL_RenderClear(rend);

        mark_dest.x = getOX() - mark_dest.w / 2;
        mark_dest.y = getOY() - mark_dest.h / 2;
        // SDL_RenderCopy(rend, mark, NULL, &mark_dest);
        DrawCircle( rend, 
            getOX() - mark_dest.w / 2,
            getOY() - mark_dest.h / 2,
            10,
            0xaa00aa
        );


        for (int _i = 0; _i < 4; _i ++)
        {
            DrawCircle( rend, 
                v1.TurnStates[_i].position[0],
                v1.TurnStates[_i].position[1],
                10,
                0xaa0000
            );
            // dest.x = v1.TurnStates[_i].position[0] - dest.w / 2;
            // dest.y = v1.TurnStates[_i].position[1] - dest.h / 2;
            // SDL_RenderCopyEx(rend, tex, NULL, &dest, RAD_TO_DEG(-v1.TurnStates[_i].rotation), NULL, SDL_FLIP_NONE);
        }
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy texture
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(mark);

    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}