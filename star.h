#ifndef STAR_H
#define STAR_H

#include "SDL2/SDL.h"
#include "simpleMatrix.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "smoothStep.h"

class Star
{
    private:
        int id;

        double ra;
        double dec;
        double parallax;

        int colorGrad = 0;

        std::string name;
        std::string spectral_class;
        std::string info;
        std::vector<std::vector<double>> worldSpacePos; //Calculated at star creation from starData
        std::vector<std::vector<double>> rotatedWorldSpacePos; //Rotated point in 3d
        const double PI = 3.14159265359;

        void CalcWorldPos();

    public:
        Star(std::vector<std::string> inputInfo, std::vector<double> inputData, int i);
        ~Star();

        bool selected = false;
        std::vector<std::vector<double>> screenSpacePos {{0}, {0}}; //Updated at runtime (x, y)

        void UpdateStarScreenPos(double rotX, double rotY, double rotZ);
        void RenderStar(SDL_Renderer* renderer, int xOffset, int yOffset);
        const char* GetName();
};


#endif