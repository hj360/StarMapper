#include "HUI.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::setActivePage(int page)
{
    activePage = page;
}

void UI::genUIPage(const char* title)
{
    pages.push_back(HUI_Page(title));
}

void UI::RenderPage(SDL_Renderer *renderer)
{
    pages[activePage].RenderPage(renderer);
    //Base layer last
    pages[0].RenderPage(renderer);
}

void UI::UpdateActivePageInteractive(SDL_Point *p)
{
    pages[activePage].UpdateInteractiveElements(p, elementIsInteractive);

    //Prevent base layer decision from overriding one already determined by a non-base button
    if(elementIsInteractive == SDL_TRUE)
    {
        return;
    }
    //Check base layer last if no other button is hovered
    pages[0].UpdateInteractiveElements(p, elementIsInteractive);
}