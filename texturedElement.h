#ifndef TEXTUREDELEMENT_H
#define TEXTUREDELEMENT_H

#include "textureManager.h"
#include "smoothStep.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class texturedElement
{
    private:
        SDL_Rect tex_rect;
        SDL_Texture* texture = nullptr;

    public:
        texturedElement(int w, int h, int x, int y, const std::string &file, SDL_Renderer *renderer);
        ~texturedElement();

        void Render(SDL_Renderer *renderer);
};

class textElement
{
    private:
        SDL_Surface* textSurf = nullptr;
        SDL_Texture* texture = nullptr;
        TTF_Font* font = nullptr;
        const char* text;
        SDL_Rect textRect;
        int tex_w = 0;
        int tex_h = 0;
        int colorGrad = 0;

    public:
        textElement(TTF_Font* inFont);
        ~textElement();

        void RenderText(SDL_Renderer *renderer, SDL_Color color, int x, int y, const char* inText, bool smooth = 0);
};

#endif