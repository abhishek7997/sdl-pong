// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2
// On Windows: g++ main.cpp -o prog.exe -IC:\mingw_sdl\include\SDL2 -LC:\mingw_sdl\lib -lmingw32 -lSDL2main -lSDL2
// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Third-party library
#include <SDL.h>
#include "TextureRectangle.hpp"
#include "ResourceManager.hpp"
#include "SDLApp.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "DynamicText.hpp"

#define WIDTH 640
#define HEIGHT 480
#define FPS 60

SDLApp *app;
int mouseX;
int mouseY;
GameObject *object1;
GameObject *object2;
Sound *CollisionSound;

void HandleEvents()
{
    SDL_Event event;
    int mouseX;
    int mouseY;
    Uint32 buttons;
    buttons = SDL_GetMouseState(&mouseX, &mouseY);

    Uint32 starttime = SDL_GetTicks();
    while (SDL_PollEvent(&event))
    {
        // 1) Handle input
        if (event.type == SDL_QUIT)
        {
            app->StopAppLoop();
            break;
        }
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            std::cout << "Left button pressed" << std::endl;
            if (object2->GetCollider2D().IsColliding(object1->GetCollider2D()))
            {
                std::cout << "Is Colliding" << std::endl;
                CollisionSound->PlaySound();
            }
            else
            {
                std::cout << "Not colliding" << std::endl;
            }
        }
    }
    Uint32 endtime = SDL_GetTicks();
    Uint32 deltatime = endtime - starttime;

    if (deltatime > (1000 / FPS))
    {
    }
    else
    {
        SDL_Delay((1000 / FPS) - deltatime);
    }
}

void HandleUpdates()
{
    object1->Update();
    object2->Update();
    object1->GetCollider2D().SetAbsolutePosition(object1->GetSprite().GetPositionX(), object1->GetSprite().GetPositionY());
    object1->GetCollider2D().SetDimensions(object1->GetSprite().GetWidth(), object1->GetSprite().GetHeight());

    object2->GetCollider2D().SetAbsolutePosition(object2->GetSprite().GetPositionX(), object2->GetSprite().GetPositionY());
    object2->GetCollider2D().SetDimensions(object2->GetSprite().GetWidth(), object2->GetSprite().GetHeight());
}

void HandleRendering()
{
    DynamicText text1("./assets/fonts/8bitOperatorPlus-Regular.ttf", 32);
    text1.DrawText(app->GetRenderer(), "SDL2 Text Demo", 0, 0, 400, 100);

    object1->GetSprite().SetPosition(app->GetMouseX(), app->GetMouseY());
    object1->GetSprite().SetDimension(100, 100);

    object2->GetSprite().SetPosition(150, 170);
    object2->GetSprite().SetDimension(100, 100);

    object1->Render();
    object2->Render();
}

int main(int argc, char *argv[])
{
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "New SDL2 Abstraction", 20, 20, 640, 480);
    app->SetMaxFrameRate(8);
    object1 = new GameObject(app->GetRenderer(), "./assets/images/chess.bmp");
    object2 = new GameObject(app->GetRenderer(), "./assets/images/chess.bmp");
    CollisionSound = new Sound("./assets/sounds/collide.wav");
    CollisionSound->SetupDevice();
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdates);
    app->SetRenderCallback(HandleRendering);
    app->RunLoop();

    delete app;
    delete object1;
    delete object2;
    delete CollisionSound;
    return 0;
}
