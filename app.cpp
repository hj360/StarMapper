#include "app.h"

App::App(){}
App::~App(){}

void App::InitSystems(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    //Init SDL systems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cerr << "Error! SDL Failed to init!" << std::endl;
        exit(-1);
    } else {
        std::cout << "SDL Initialized!" << std::endl;
    }
    //Initialize SDL TTF for font rendering
    if(TTF_Init() == -1)
    {
        std::cerr << "Error! TTF Failed to init!" << std::endl;
        exit(-1);
    } else {
        std::cout << "TTF Initialized!" << std::endl;
    }
    //Set window to a new SDL window
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    //Check for potential window errors 
    if(window != nullptr)
    {
        std::cout << "SDL Window created!" << std::endl;
    } else {
        std::cerr << "SDL Window creation failed! Exiting..." << std::endl;
        exit(-1);
    }
    //set renderer to a new SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Check renderer for errors
    if(window != nullptr)
    {
        std::cout << "SDL Renderer created!" << std::endl;
    } else {
        std::cerr << "SDL Renderer creation failed! Exiting..." << std::endl;
        exit(-1);
    }

    isRunning = true;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    SDL_SetWindowResizable(window, SDL_TRUE);

    //Dynamic display size
    currentDisplayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_GetDisplayBounds(currentDisplayIndex, &display_bounds);

    screen_h = display_bounds.h/1.2;
    screen_w = display_bounds.w/1.2;

    SDL_SetWindowSize(window, screen_w, screen_h);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    //Set up starfield
    starField = new StarManager("res/stars.txt");
    //Create a UI system
    starUI = new UI();
}

void App::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
        {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            isRunning = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT:
                            mouseLeftPressed = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button) {
                        case SDL_BUTTON_LEFT:
                            mouseLeftPressed = false;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

}

void App::Update()
{
    //Update mouse position
    HandleMouse();
    //Handle star rotation
    starField->UpdateStarPos(mouse_y/100, mouse_x/100, 0);
    //Handle UI
    starUI->UpdateActivePageInteractive(&mousePos);
    starUI->setActivePage(0);
}

void App::Render()
{
    SDL_SetRenderDrawColor(renderer, 14, 17, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    //Render sol
    filledCircleRGBA(renderer, screen_w/2, screen_h/2, 2, 255, 255, 255, 255);
    aacircleRGBA(renderer, screen_w/2, screen_h/2, 2, 255, 255, 255, 255);
    //Render all stars in database
    starField->RenderAllStars(renderer, screen_w/2, screen_h/2, mousePos);
    //Render UI
    starUI->RenderPage(renderer);
    //Render selected star name
    mainText->RenderText(renderer, {255, 255, 255}, starField->GetCurrentStarScreenPos(screen_w/2, screen_h/2).x, starField->GetCurrentStarScreenPos(screen_w/2, screen_h/2).y - 40, starField->GetCurrentStarName(), 1);

    SDL_RenderPresent(renderer);

}

void App::Clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(BaiJamjuree_20);
    TTF_CloseFont(BaiJamjuree_12);
    SDL_Quit();
}

void App::HandleMouse()
{
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    //Lerp smoothly to mouse position if left is clicked
    if(mouseLeftPressed == 1 && mouseLeftPressedLast == 0)
    {
        mouseLeftPressedLast = mouseLeftPressed;
        mouseStart = mousePos;
        mouse_x_last = mouse_x;
        mouse_y_last = mouse_y;

    } else if(mouseLeftPressed == 0 && mouseLeftPressedLast == 1)
    {
        mouseLeftPressedLast = 0;
    }

    if(mouseLeftPressed == true)
    {
        lerp_to_x = mousePos.x - mouseStart.x;
        lerp_to_y = mousePos.y - mouseStart.y;
    }

    deltaX = lerp_to_x - (mouse_x - mouse_x_last);
    deltaY = lerp_to_y - (mouse_y - mouse_y_last);

    mouse_x += (deltaX * 0.05);
    mouse_y += (deltaY * 0.05);
}

void App::LoadTextures()
{
    splashLogo = new texturedElement(300, 157, screen_w/2, (screen_h/2)-100, "res/img/logo.bmp", renderer);
    openText = new textElement(BaiJamjuree_20);
    mainText = new textElement(BaiJamjuree_12);
}

void App::LoadFonts()
{
    BaiJamjuree_20 = TTF_OpenFont("res/fonts/BaiJamjuree-Regular.ttf", 20);
    BaiJamjuree_12 = TTF_OpenFont("res/fonts/BaiJamjuree-Regular.ttf", 12);
}

void App::LoadUI()
{
    //Initialize pages
    starUI->genUIPage("MainOverlay");
    //Fill pages
    //Main overlay
    starUI->pages[0].AddTexturedButton(51, 29, screen_w-25, 14, "res/img/ui/exit.bmp", renderer, {18, 18, 18}, {255, 0, 0});
}

void App::SplashScreen()
{
    SDL_SetRenderDrawColor(renderer, 14, 17, 21, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    splashLogo->Render(renderer);
    openText->RenderText(renderer, {255, 255, 255}, (screen_w/2), (screen_h/2)+50, "POWERED BY                             INTERPLANETARY", 0);
    openText->RenderText(renderer, {255, 255, 255, 255}, (screen_w/2) - 24, (screen_h/2)+50, "SAGITTARIUS", 1);
    //openText = new textElement(BaiJamjuree_20, renderer, "POWERED BY SAGITTARIUS INTERPLANETARY", {255, 255, 255}, screen_w/2, (screen_h/2) + 200);

    SDL_RenderPresent(renderer);    
}