#include "textureManager.h"

//Load textures
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    //Check vadility of image load
    if(loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);

        if(texture == nullptr)
        {
            std::cout << "Create Texture from surface error!" << std::endl;
        }
    }

    return texture;
}