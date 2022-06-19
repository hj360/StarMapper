#include "texturedElement.h"

texturedElement::texturedElement(int w, int h, int x, int y, const std::string &file, SDL_Renderer *renderer)
{
    tex_rect.w = w;
    tex_rect.h = h;

    tex_rect.x = x - w/2;
    tex_rect.y = y - h/2;

    texture = loadTexture(file, renderer);
}

texturedElement::~texturedElement()
{

}

void texturedElement::Render(SDL_Renderer *renderer)
{    
    SDL_RenderCopyEx(renderer, this->texture, NULL, &this->tex_rect, 0, NULL, SDL_FLIP_NONE);
}

textElement::textElement(TTF_Font* inFont)
{
    font = inFont;
}


textElement::~textElement()
{

}

void textElement::RenderText(SDL_Renderer *renderer, SDL_Color color, int x, int y, const char* inText, bool smooth)
{   
    text = inText;

    if(smooth)
    {
        float smoothVal = smoothstep(0, 200, colorGrad);
        color.r = 255*smoothVal;
        color.g = 255*smoothVal;
        color.b = 255*smoothVal;

        textSurf = TTF_RenderText_Blended(font, text, color);
        ++colorGrad;
    } else {
        textSurf = TTF_RenderText_Blended(font, text, color);
    }

    texture = SDL_CreateTextureFromSurface(renderer, textSurf);
    SDL_FreeSurface(textSurf);
    SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
    
    //Center text with rect size offset
    textRect = {x-(tex_w/2), y-(tex_h/2), tex_w, tex_h};

    SDL_RenderCopy(renderer, this->texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
}