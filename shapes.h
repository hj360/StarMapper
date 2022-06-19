#ifndef SHAPES_H
#define SHAPES_H

#include "SDL2/SDL.h"

static void RenderFilledCircle(int radius, int x0, int y0, SDL_Renderer *renderer)
{
    int x = radius;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = (dx - (radius + radius));

    while(x >= y)
    {
        SDL_RenderDrawLine(renderer, (x0 - y), (y0 - x), (x0 + y), (y0 - x));
        SDL_RenderDrawLine(renderer, (x0 - x), (y0 - y), (x0 + x), (y0 - y));
        SDL_RenderDrawLine(renderer, (x0 - x), (y0 + y), (x0 + x), (y0 + y));
        SDL_RenderDrawLine(renderer, (x0 - y), (y0 + x), (x0 + y), (y0 + x));


        if(err <= 0)
        {
            ++y;
            err += dy;
            dy += 2;
        }

        if(err > 0)
        {
            --x;
            dx += 2;
            err += (dx - (radius + radius));
        }

    }

};

#endif