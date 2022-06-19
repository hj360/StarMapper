#define WIDTH 600
#define HEIGHT 600

//Sets frame rate for the app
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
    
    //Starting control loop
    while(1)
    {
        //Render splash screen if this is the first loop
        mainApp->SplashScreen();
        //Wait until splash screen is finished
        if(SDL_GetTicks() > 3000)
        {
            break;
        }

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL; 
    }

    //Main control loop
    while(mainApp->isRunning)
    {
        mainApp->HandleEvents();
        mainApp->Update();
        mainApp->Render();

        //Wait until next frame
        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

    //Shutdown the app
    mainApp->Clean();

    return 0;
}

