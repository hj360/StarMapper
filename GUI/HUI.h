#ifndef HUI_H
#define HUI_H

#include "HUI_page.h"
#include <vector>
#include <SDL2/SDL.h>

class UI
{
    private:
        int activePage = 0;

    public:
        UI();
        ~UI();

        std::vector<HUI_Page> pages {};

        SDL_bool elementIsInteractive = SDL_FALSE;

        void setActivePage(int page);
        void genUIPage(const char* title);
        void RenderPage(SDL_Renderer *renderer);
        void UpdateActivePageInteractive(SDL_Point *p);
        

};

#endif