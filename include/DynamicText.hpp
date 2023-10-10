#ifndef DYNAMICTEXT_HPP
#define DYNAMICTEXT_HPP

/*
    DynamicText objects can change, but they are more expensive to use
    because the textures are constantly recreated each frame.
*/

#include <SDL_ttf.h>
#include <iostream>

class DynamicText
{
public:
    DynamicText(std::string fontfilepath, size_t fontSize);
    ~DynamicText();
    void DrawText(SDL_Renderer *renderer, std::string text, int x, int y, int w, int h);

private:
    static bool s_ttfInitialized;
    TTF_Font *m_font;
    SDL_Rect m_rectangle;
    SDL_Texture *m_texture;
    SDL_Surface *m_surface;
};

#endif