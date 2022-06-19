#include "HUI_page.h"

HUI_Page::HUI_Page(const char* title)
{
    pageTitle = title;
}

HUI_Page::~HUI_Page()
{

}

void HUI_Page::AddButton(int w, int h, int x, int y, std::vector<float> inColor, std::vector<float> outColor)
{
    pageButtons.push_back(Button(w, h, x, y, inColor, outColor));
}

void HUI_Page::AddTexturedButton(int w, int h, int x, int y, const std::string &file, SDL_Renderer* renderer, std::vector<float> inColor, std::vector<float> outColor)
{
    pageButtons.push_back(Button(w, h, x, y, file, renderer, inColor,  outColor));
}

void HUI_Page::AddTexturedElement(int w, int h, int x, int y, const std::string &file, SDL_Renderer *renderer)
{
    pageElements.push_back(texturedElement(w, h, x, y, file, renderer));
}

void HUI_Page::UpdateInteractiveElements(const SDL_Point *p, SDL_bool &interactiveElement)
{
    interactiveElement = SDL_FALSE;
    //Change button color on hover
    for(int i = 0; i < pageButtons.size(); ++i)
    {
        
        if(pageButtons[i].isPointed(p))
        {
            interactiveElement = SDL_TRUE;

            float smoothVal = smoothstep(0, 30, pageButtons[i].colorGrad);
            pageButtons[i].SetColor({
                (pageButtons[i].GetBaseColor()[0] + ((pageButtons[i].GetSecondColor()[0])-(pageButtons[i].GetBaseColor()[0])) * smoothVal),
                (pageButtons[i].GetBaseColor()[1] + ((pageButtons[i].GetSecondColor()[1])-(pageButtons[i].GetBaseColor()[1])) * smoothVal),
                (pageButtons[i].GetBaseColor()[2] + ((pageButtons[i].GetSecondColor()[2])-(pageButtons[i].GetBaseColor()[2])) * smoothVal)
            });

            
            pageButtons[i].colorGrad++;

        } else {
            pageButtons[i].SetBaseColor();
            pageButtons[i].colorGrad = 0;
        }
    }
}

void HUI_Page::RenderPage(SDL_Renderer *renderer)
{
    for(int i = 0; i < pageElements.size(); ++i)
    {
        pageElements[i].Render(renderer);
    }

    for(int i = 0; i < pageButtons.size(); ++i)
    {
        pageButtons[i].render(renderer);
    }
}