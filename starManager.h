#ifndef STARMANAGER_H
#define STARMANAGER_H

#include "SDL2/SDL.h"
#include "star.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "smoothStep.h"

#include <fstream>

class StarManager
{
    private:
        std::vector<std::vector<double>> starData;
        std::vector<std::vector<std::string>> starInfo;

        std::vector<Star> starSet;

        void LoadStars(const char* starFile);
        void CreateStars();
        int currentStarIndex = 0;
        int numStars = 0;
        int selectedSmoothGrad = 0;

    public:
        StarManager(const char* starFile);
        ~StarManager();

        void UpdateStarPos(double rotX, double rotY, double rotZ);
        void RenderAllStars(SDL_Renderer *renderer, int xOffset, int yOffset, SDL_Point cursor);

        void RenderSelectedLine(SDL_Renderer *renderer, int xOffset, int yOffset);

        const char* GetCurrentStarName();
        SDL_Point GetCurrentStarScreenPos(int xOffset, int yOffset);
        void GetCurrentStarData();

};


#endif