#include "star.h"

Star::Star(std::vector<std::string> inputInfo, std::vector<double> inputData, int i)
{
    name = inputInfo[0];
    spectral_class = inputInfo[1];
    info = inputInfo[2];

    ra = inputData[0];
    dec = inputData[1];
    parallax = inputData[2];

    id = i;

    CalcWorldPos();
}

Star::~Star(){}

//Converts galactic coords to xyz
void Star::CalcWorldPos()
{
    ra = ra * PI/180;
    dec = dec * PI/180;

    double radius = 1/(parallax/700);

    double x = 100 * radius * sin(ra) * cos(dec);
    double y = 100 * radius * sin(ra) * sin(dec);
    double z = 100 * radius * cos(ra);

    worldSpacePos = {{x}, {y}, {z}};

}

void Star::UpdateStarScreenPos(double rotX, double rotY, double rotZ)
{
    //Calc rotations
    this->rotatedWorldSpacePos = Rotate_3D(this->worldSpacePos, rotX, rotY, rotZ);
    //Transform to 2d projection
    Project_2D(this->rotatedWorldSpacePos, this->screenSpacePos);
}

void Star::RenderStar(SDL_Renderer *renderer, int xOffset, int yOffset)
{
    if(selected == true)
    {
        float smoothVal = smoothstep(0, 20, colorGrad);            
        aacircleRGBA(renderer, screenSpacePos[0][0] + xOffset, screenSpacePos[1][0] + yOffset, 20*smoothVal, 255, 255, 255, 255*smoothVal);
        filledCircleRGBA(renderer, screenSpacePos[0][0] + xOffset, screenSpacePos[1][0] + yOffset, 2, 255, 255, 255, 255);
        aacircleRGBA(renderer, screenSpacePos[0][0] + xOffset, screenSpacePos[1][0] + yOffset, 2, 255, 255, 255, 255);
        colorGrad++;
    } else {
        colorGrad = 0;
        filledCircleRGBA(renderer, screenSpacePos[0][0] + xOffset, screenSpacePos[1][0] + yOffset, 1, 255, 255, 255, 255);
    }
    
}

const char* Star::GetName()
{
    return name.c_str();
}