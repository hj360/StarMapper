#include "starManager.h"

StarManager::StarManager(const char* starFile)
{
    LoadStars(starFile);
    CreateStars();
}

StarManager::~StarManager(){}

void StarManager::LoadStars(const char* starFile)
{
    std::ifstream file(starFile);

    std::string name, spectral_class, genInfo, ra, dec, parallax;

    if(file.is_open())
    {
        int starIndex = 0;

        while(!file.eof())
        {
            //Temp vectors to store star info and data
            std::vector<std::string> info;
            std::vector<double> data;

            std::getline(file, name, ',');
            info.push_back(name);

            std::getline(file, spectral_class, ',');
            info.push_back(spectral_class);

            std::getline(file, genInfo, ',');
            info.push_back(genInfo);

            std::getline(file, ra, ',');
            data.push_back(stod(ra));

            std::getline(file, dec, ',');
            data.push_back(stod(dec));

            std::getline(file, parallax, ',');
            data.push_back(stod(parallax));

            //Push info and data to starfield vectors
            starInfo.push_back(info);
            starData.push_back(data);

            ++starIndex;

        }

        numStars = starIndex;
    }

    file.close();
}

void StarManager::CreateStars()
{
    for(int i = 0; i < numStars; ++i)
    {
        //Create star
        Star tempStar(starInfo[i], starData[i], i);
        //Add star to dataset
        starSet.push_back(tempStar);
    }
}

void StarManager::UpdateStarPos(double rotX, double rotY, double rotZ)
{
    for(int i = 0; i < starSet.size(); ++i)
    {
        starSet[i].UpdateStarScreenPos(rotX, rotY, rotZ);
    }
}

void StarManager::RenderAllStars(SDL_Renderer *renderer, int xOffset, int yOffset, SDL_Point cursor)
{
    //Render each star in the set of stars
    for(int i = 0; i < starSet.size(); ++i)
    {
        if(starSet[i].screenSpacePos[0][0] + xOffset < (cursor.x + 10) && starSet[i].screenSpacePos[0][0] + xOffset > (cursor.x - 10) && starSet[i].screenSpacePos[1][0] + yOffset < (cursor.y + 10) && starSet[i].screenSpacePos[1][0] + yOffset > (cursor.y - 10))
        {
            starSet[i].selected = true;
            currentStarIndex = i;
            starSet[i].RenderStar(renderer, xOffset, yOffset);
        } else{
            starSet[i].selected = false;
            starSet[i].RenderStar(renderer, xOffset, yOffset);
        }
        
    }
}

void StarManager::RenderSelectedLine(SDL_Renderer *renderer, int xOffset, int yOffset)
{
    if(starSet[currentStarIndex].selected == true)
    {
        float smoothVal = smoothstep(0, 20, selectedSmoothGrad);
        int endX = (xOffset * (1-smoothVal)) + ((starSet[currentStarIndex].screenSpacePos[0][0] + xOffset) * smoothVal);
        int endY = (yOffset * (1-smoothVal)) + ((starSet[currentStarIndex].screenSpacePos[1][0] + yOffset) * smoothVal);
        aalineRGBA(renderer, endX, endY + 20, xOffset, yOffset, 255, 255, 255, 255);
        ++selectedSmoothGrad;

    } else {
        selectedSmoothGrad = 0;
        aalineRGBA(renderer, starSet[currentStarIndex].screenSpacePos[0][0] + xOffset, starSet[currentStarIndex].screenSpacePos[1][0] + yOffset + 20, xOffset, yOffset, 255, 255, 255, 255);
    }
    
}

const char* StarManager::GetCurrentStarName()
{
    return starSet[currentStarIndex].GetName();
}

SDL_Point StarManager::GetCurrentStarScreenPos(int xOffset, int yOffset)
{
    SDL_Point starPos = {int(starSet[currentStarIndex].screenSpacePos[0][0]) + xOffset, int(starSet[currentStarIndex].screenSpacePos[1][0]) + yOffset};
    return starPos;
}

void StarManager::GetCurrentStarData()
{

}