#include "SDLApp.hpp"

SDLApp::SDLApp(Uint32 systemFlags, std::string title, int x, int y, int w, int h)
{
    m_width = w;
    m_height = h;
    m_maxFrameRate = 60;
    if (SDL_Init(systemFlags) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }

    m_window = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}
SDLApp::~SDLApp()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLApp::SetEventCallback(std::function<void(void)> func)
{
    m_EventCallback = func;
}

void SDLApp::SetUpdateCallback(std::function<void(void)> func)
{
    m_UpdateCallback = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func)
{
    m_RenderCallback = func;
}

void SDLApp::RunLoop()
{
    while (m_isRunning)
    {
        Uint32 starttime = SDL_GetTicks();
        Uint32 buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
        m_EventCallback();
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        m_UpdateCallback();
        m_RenderCallback();
        SDL_RenderPresent(m_renderer);
        Uint32 endtime = SDL_GetTicks();
        Uint32 deltatime = endtime - starttime;

        if (deltatime <= (1000 / m_maxFrameRate))
        {
            SDL_Delay((1000 / m_maxFrameRate) - deltatime);
        }
    }
}

void SDLApp::SetMaxFrameRate(int maxFrameRate)
{
    m_maxFrameRate = maxFrameRate;
}

SDL_Renderer *SDLApp::GetRenderer() const
{
    return m_renderer;
}

int SDLApp::GetMouseX()
{
    return m_mouseX;
}

int SDLApp::GetMouseY()
{
    return m_mouseY;
}

int SDLApp::GetWindowWidth()
{
    return m_width;
}

int SDLApp::GetWindowHeight()
{
    return m_height;
}

void SDLApp::StopAppLoop()
{
    m_isRunning = false;
}