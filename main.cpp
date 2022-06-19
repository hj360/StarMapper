#define WIDTH 600
#define HEIGHT 600

#define TICK_INTERVAL 20

#include "app.h"

static Uint32 next_time;

Uint32 time_left()
{
    Uint32 now;
    now = SDL_GetTicks();
    if(next_time <= now)
    {
        return 0;
    } else {
        return next_time - now;
    }
}

int main(int argc, char* argv[])
{
    App *mainApp = new App();

    mainApp->InitSystems("StarField", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    mainApp->LoadFonts();
    mainApp->LoadTextures();
    mainApp->LoadUI();
    

    while(1)
    {
        mainApp->SplashScreen();

        if(SDL_GetTicks() > 3000)
        {
            break;
        }

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL; 
    }

    while(mainApp->isRunning)
    {
        mainApp->HandleEvents();
        mainApp->Update();
        mainApp->Render();

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

    mainApp->Clean();

    return 0;
}

