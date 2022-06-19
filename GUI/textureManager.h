#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);

#endif