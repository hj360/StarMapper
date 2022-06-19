#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <iostream>

#include "starManager.h"
#include "HUI.h"
#include "texturedElement.h"
#include <SDL2/SDL_ttf.h>

class App
{
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        StarManager* starField = nullptr;

        UI* starUI = nullptr;

        SDL_Rect display_bounds;
        int screen_w;
        int screen_h;
        int currentDisplayIndex;

        SDL_Point mousePos;
        SDL_Point mouseStart;
        bool mouseLeftPressed = false;
        bool mouseLeftPressedLast = false;
        double mouse_x = 0;
        double mouse_y = 0;
        double mouse_x_last = 0;
        double mouse_y_last = 0;
        double lerp_to_x = 0;
        double lerp_to_y = 0;
        double deltaX = 0;
        double deltaY = 0;

        //Textures
        texturedElement* splashLogo = nullptr;
        textElement* openText = nullptr;
        textElement* mainText = nullptr;

        //Fonts
        TTF_Font* BaiJamjuree_20 = nullptr;
        TTF_Font* BaiJamjuree_12 = nullptr;

    public:
        App();
        ~App();

        void InitSystems(const char *title, int x, int y, int w, int h, Uint32 flags);
        void HandleEvents();
        void Update();
        void Render();
        void Clean();

        void HandleMouse();
        void SplashScreen();
        void LoadTextures();
        void LoadFonts();
        void LoadUI();

        bool isRunning;
        SDL_Point getMousePos();

};


#endif