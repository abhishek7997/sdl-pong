#ifndef TEXTURERECTANGLE_HPP
#define TEXTURERECTANGLE_HPP

#include <string>
// Third-party library
#include <SDL.h>

#ifndef WIDTH
#define WIDTH 640
#endif

#ifndef HEIGHT
#define HEIGHT 480
#endif

class TextureRectangle
{
public:
    TextureRectangle(SDL_Renderer *renderer, std::string filepath);
    TextureRectangle(SDL_Renderer *renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);
    ~TextureRectangle();
    void InitDefaults();
    void Draw(const int x, const int y, const int w, const int h);
    void SetPosition(const int x, const int y);
    void SetDimension(const int w, const int h);
    int GetPositionX();
    int GetPositionY();
    int GetWidth();
    int GetHeight();
    void Update();
    void Render(SDL_Renderer *renderer);

private:
    inline SDL_Rect GetRectangle() const { return m_rectangle; }
    SDL_Rect m_rectangle;
    SDL_Texture *m_texture;
    int m_redColorKey;
    int m_greenColorKey;
    int m_blueColorKey;
};

#endif