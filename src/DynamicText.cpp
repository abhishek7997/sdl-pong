#include "DynamicText.hpp"

bool DynamicText::s_ttfInitialized = false;

DynamicText::DynamicText(std::string fontfilepath, size_t fontSize)
{
    if (!s_ttfInitialized && (TTF_Init() == -1))
    {
        std::cout << "Could not initialize SDL_ttf, error: " << SDL_GetError() << std::endl;
        return;
    }

    m_font = TTF_OpenFont(fontfilepath.c_str(), fontSize);
    if (m_font == nullptr)
    {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    s_ttfInitialized = true;
}

DynamicText ::~DynamicText()
{
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
}

void DynamicText::DrawText(SDL_Renderer *renderer, std::string text, int x, int y, int w, int h)
{
    m_surface = TTF_RenderText_Solid(m_font, text.c_str(), {255, 255, 255});
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    SDL_FreeSurface(m_surface);

    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}
