#ifndef BUTTON_H
#define BUTTON_H

#include "textureManager.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Button
{
    private:
        SDL_Rect button_rect;
        std::vector<float> baseColor {255, 255, 255};
        std::vector<float> secondColor {255, 255, 255};
        std::vector<float> color {255, 255, 255};
        SDL_Texture *texture = nullptr;

    public:
        Button(int w, int h, int x, int y, std::vector<float> inColor = {255, 255, 255}, std::vector<float> outColor = {18, 18, 18});
        Button(int w, int h, int x, int y, const std::string &file, SDL_Renderer* renderer, std::vector<float> inColor = {255, 255, 255}, std::vector<float> outColor = {18, 18, 18});
        ~Button();

        int colorGrad = 0;

        void SetColor(std::vector<float> newColor);
        void SetBaseColor();
        void SetSecondColor();
        std::vector<float> GetBaseColor();
        std::vector<float> GetSecondColor();
        SDL_bool isPointed(const SDL_Point *p);
        SDL_bool isPressed(const SDL_Point *p, SDL_bool *mouseLeftPressed);
        void render(SDL_Renderer* renderer);

};



#endif