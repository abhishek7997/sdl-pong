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

GameObject *leftPaddle;
GameObject *rightPaddle;
GameObject *ball;

Sound *CollisionSound;
Sound *ScoreSound;

// std::string leftScoreText = "left: " + std::to_string(gameState.leftScore);
// std::string rightScoreText = "right: " + std::to_string(gameState.rightScore);

std::string leftScoreText;
std::string rightScoreText;

struct GameState
{
    float movementSpeed;
    float ballSpeed;
    float dx;
    float dy;
    int leftScore;
    int rightScore;
} gameState;

void HandleEvents()
{
    SDL_Event event;
    int mouseX;
    int mouseY;
    Uint32 buttons;
    buttons = SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event))
    {
        // 1) Handle input
        if (event.type == SDL_QUIT)
        {
            app->StopAppLoop();
            break;
        }
        else if (event.type = SDL_KEYDOWN)
        {
            // Handle keypress for moving left and right paddles
            int xr = rightPaddle->GetSprite().GetPositionX();
            int yr = rightPaddle->GetSprite().GetPositionY();
            int hr = rightPaddle->GetSprite().GetHeight();

            int xl = leftPaddle->GetSprite().GetPositionX();
            int yl = leftPaddle->GetSprite().GetPositionY();
            int hl = leftPaddle->GetSprite().GetHeight();

            switch (event.key.keysym.sym)
            {
            case SDLK_i:
                if (yr - gameState.movementSpeed >= 0)
                    rightPaddle->GetSprite().SetPosition(xr, yr - gameState.movementSpeed);
                break;
            case SDLK_k:
                if (yr + gameState.movementSpeed + hr <= HEIGHT)
                    rightPaddle->GetSprite().SetPosition(xr, yr + gameState.movementSpeed);
                break;
            case SDLK_w:
                if (yl - gameState.movementSpeed >= 0)
                    leftPaddle->GetSprite().SetPosition(xl, yl - gameState.movementSpeed);
                break;
            case SDLK_s:
                if (yl + gameState.movementSpeed + hl <= HEIGHT)
                    leftPaddle->GetSprite().SetPosition(xl, yl + gameState.movementSpeed);
                break;
            default:
                break;
            }
        }
    }
}

void HandleUpdates()
{
    int x = ball->GetSprite().GetPositionX();
    int y = ball->GetSprite().GetPositionY();

    if (leftPaddle->GetCollider2D().IsColliding(ball->GetCollider2D()))
    {
        gameState.dx *= -1;
        CollisionSound->PlaySound();
    }
    else if (rightPaddle->GetCollider2D().IsColliding(ball->GetCollider2D()))
    {
        gameState.dx *= -1;
        CollisionSound->PlaySound();
    }

    if (x + gameState.dx < 0 || x + gameState.dx >= WIDTH - 16)
        gameState.dx *= -1.0f;

    if (y + gameState.dy < 0 || y + gameState.dy >= HEIGHT - 16)
        gameState.dy *= -1.0f;

    int nx = x + gameState.dx;
    int ny = y + gameState.dy;

    if (nx + 16 > WIDTH - 5)
    {
        gameState.leftScore += 1;
        leftScoreText = "left: " + std::to_string(gameState.leftScore);
        ball->GetSprite().SetPosition(WIDTH / 2 + 8, HEIGHT / 2 + 8);
    }
    else if (nx < 5)
    {
        gameState.rightScore += 1;
        rightScoreText = "right: " + std::to_string(gameState.rightScore);
        ball->GetSprite().SetPosition(WIDTH / 2 + 8, HEIGHT / 2 + 8);
    }
    else
    {
        ball->GetSprite().SetPosition(nx, ny);
    }

    leftPaddle->Update();
    rightPaddle->Update();
    ball->Update();

    CollisionSound->StopSound();
}

void HandleRendering()
{
    leftPaddle->Render();
    rightPaddle->Render();
    ball->Render();

    DynamicText leftScore("./assets/fonts/8bitOperatorPlus-Regular.ttf", 32);
    DynamicText rightScore("./assets/fonts/8bitOperatorPlus-Regular.ttf", 32);

    leftScore.DrawText(app->GetRenderer(), leftScoreText, 50, 0, 100, 50);
    rightScore.DrawText(app->GetRenderer(), rightScoreText, 500, 0, 100, 50);
}

int main(int argc, char *argv[])
{
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "SDL2 Pong Game", 20, 20, 640, 480);
    app->SetMaxFrameRate(FPS);

    leftPaddle = new GameObject(app->GetRenderer(), "./assets/images/leftpaddle.bmp");
    leftPaddle->GetSprite().SetPosition(0, 0);
    leftPaddle->GetSprite().SetDimension(10, HEIGHT / 3);

    rightPaddle = new GameObject(app->GetRenderer(), "./assets/images/rightpaddle.bmp");
    rightPaddle->GetSprite().SetPosition(WIDTH - 10, 0);
    rightPaddle->GetSprite().SetDimension(10, HEIGHT / 3);

    ball = new GameObject(app->GetRenderer(), "./assets/images/ball.bmp");
    ball->GetSprite().SetPosition(WIDTH / 2 + 8, HEIGHT / 2 + 8);
    ball->GetSprite().SetDimension(16, 16);

    CollisionSound = new Sound("./assets/sounds/collide.wav");
    CollisionSound->SetupDevice();

    gameState.leftScore = 0;
    gameState.rightScore = 0;
    gameState.ballSpeed = 5.0f;
    gameState.movementSpeed = 5.0f;
    gameState.dx = 3.0f;
    gameState.dy = 3.0f;

    leftScoreText = "left: " + std::to_string(gameState.leftScore);
    rightScoreText = "right: " + std::to_string(gameState.rightScore);

    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdates);
    app->SetRenderCallback(HandleRendering);
    app->RunLoop();

    delete app;
    delete leftPaddle;
    delete rightPaddle;
    delete ball;
    delete CollisionSound;
    return 0;
}
