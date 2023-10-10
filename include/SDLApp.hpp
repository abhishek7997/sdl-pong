#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL.h>
#include <functional>
#include <iostream>

class SDLApp
{
public:
    SDLApp(Uint32 systemFlags, std::string title, int x, int y, int w, int h);
    ~SDLApp();
    void SetEventCallback(std::function<void(void)> func);
    void SetUpdateCallback(std::function<void(void)> func);
    void SetRenderCallback(std::function<void(void)> func);
    void RunLoop();
    void SetMaxFrameRate(int);
    SDL_Renderer *GetRenderer() const;
    int GetMouseX();
    int GetMouseY();
    int GetWindowWidth();
    int GetWindowHeight();
    void StopAppLoop();

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    bool m_isRunning = true;
    std::function<void(void)> m_EventCallback;
    std::function<void(void)> m_UpdateCallback;
    std::function<void(void)> m_RenderCallback;
    int m_maxFrameRate;
    int m_mouseX;
    int m_mouseY;
    int m_width;
    int m_height;
};

#endif