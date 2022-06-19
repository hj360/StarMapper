#ifndef HUI_PAGE_H
#define HUI_PAGE_H

#include <string>
#include "smoothStep.h"
#include "button.h"
#include "texturedElement.h"

class HUI_Page
{
    private:
        std::string pageTitle;
        std::vector<texturedElement> pageElements {};


    public:
        HUI_Page(const char* title);
        ~HUI_Page();

        std::vector<Button> pageButtons {};
        
        void AddButton(int w, int h, int x, int y, std::vector<float> inColor, std::vector<float> outColor);
        void AddTexturedButton(int w, int h, int x, int y, const std::string &file, SDL_Renderer* renderer, std::vector<float> inColor, std::vector<float> outColor);
        void AddTexturedElement(int w, int h, int x, int y, const std::string &file, SDL_Renderer *renderer);
        void UpdateInteractiveElements(const SDL_Point *p, SDL_bool &interactiveElement);
        void RenderPage(SDL_Renderer* renderer);
    
};


#endif