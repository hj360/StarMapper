#include "button.h"

Button::Button(int w, int h, int x, int y, std::vector<float> inColor, std::vector<float> outColor)
{
    //Establish default button dimensions
    button_rect.w = w;
    button_rect.h = h;

    //Default location
    button_rect.x = x - w/2;
    button_rect.y = y - h/2;

    color = inColor;
    baseColor = inColor;
    secondColor = outColor;
}

Button::Button(int w, int h, int x, int y, const std::string &file, SDL_Renderer* renderer, std::vector<float> inColor, std::vector<float> outColor)
{
    //Establish default button dimensions
    button_rect.w = w;
    button_rect.h = h;

    //Default location
    button_rect.x = x - w/2;
    button_rect.y = y - h/2;

    color = inColor;
    baseColor = inColor;
    secondColor = outColor;

    texture = loadTexture(file, renderer);
}

Button::~Button() {}

void Button::SetBaseColor()
{
    color = baseColor;
}

void Button::SetSecondColor()
{
    color = secondColor;
}

void Button::SetColor(std::vector<float> newColor)
{
    color = newColor;
}

std::vector<float> Button::GetBaseColor()
{
    return baseColor;
}

std::vector<float> Button::GetSecondColor()
{
    return secondColor;
}

//Returns a TRUE if mouse is inside button rect
SDL_bool Button::isPointed(const SDL_Point *p)
{
    return (SDL_PointInRect(p, &button_rect));
}

SDL_bool Button::isPressed(const SDL_Point *p, SDL_bool *mouseLeftPressed)
{
    if(this->Button::isPointed(p) == SDL_TRUE && *mouseLeftPressed == SDL_TRUE)
    {
        return SDL_TRUE;
    }

    return SDL_FALSE;
}

void Button::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &button_rect);

    if(texture != nullptr)
    {
        SDL_RenderCopyEx(renderer, this->texture, NULL, &this->button_rect, 0, NULL, SDL_FLIP_NONE);
    }
}