#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL.h>
#include "TextureRectangle.hpp"

class Collider2D
{
public:
    Collider2D();
    ~Collider2D();
    SDL_bool IsColliding(Collider2D &collider);
    void SetAbsolutePosition(int x, int y);
    void SetDimensions(int w, int h);
    int GetPositionX();
    int GetPositionY();
    int GetWidth();
    int GetHeight();
    SDL_Rect &GetColliderBoundingBox();

private:
    SDL_Rect *m_colliderRectangle;
};

#endif