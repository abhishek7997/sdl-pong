#include <iostream>
#include <string>
// Third-party library
#include <SDL.h>
#include "TextureRectangle.hpp"
#include "ResourceManager.hpp"

#ifndef WIDTH
#define WIDTH 640
#endif

#ifndef HEIGHT
#define HEIGHT 480
#endif

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath)
{
    SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath);
    // std::cout << "Image loaded: " << filepath.c_str() << std::endl;
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    InitDefaults();
}

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
    SDL_Surface *surface = ResourceManager::GetInstance().GetSurface(filepath);
    // std::cout << "Image loaded: " << filepath.c_str() << std::endl;
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, redColorKey, greenColorKey, blueColorKey));
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    InitDefaults();
    m_redColorKey = redColorKey;
    m_greenColorKey = greenColorKey;
    m_blueColorKey = blueColorKey;
}

void TextureRectangle::InitDefaults()
{
    m_rectangle.x = 0;
    m_rectangle.y = 0;
    m_rectangle.w = 64;
    m_rectangle.h = 64;
    m_redColorKey = 0xff;
    m_greenColorKey = 0x00;
    m_blueColorKey = 0xff;
}

TextureRectangle::~TextureRectangle()
{
    SDL_DestroyTexture(m_texture);
}

void TextureRectangle::Draw(const int x, const int y, const int w, const int h)
{
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}
void TextureRectangle::SetPosition(const int x, const int y)
{
    m_rectangle.x = x;
    m_rectangle.y = y;
}
void TextureRectangle::SetDimension(const int w, const int h)
{
    m_rectangle.w = w;
    m_rectangle.h = h;
}

int TextureRectangle::GetPositionX()
{
    return m_rectangle.x;
}

int TextureRectangle::GetPositionY()
{
    return m_rectangle.y;
}

int TextureRectangle::GetWidth()
{
    return m_rectangle.w;
}

int TextureRectangle::GetHeight()
{
    return m_rectangle.h;
}

void TextureRectangle::Update()
{
}

void TextureRectangle::Render(SDL_Renderer *renderer)
{

    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}
