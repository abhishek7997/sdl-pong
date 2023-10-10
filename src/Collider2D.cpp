#include "Collider2D.hpp"

Collider2D::Collider2D()
{
    m_colliderRectangle = new SDL_Rect;
    m_colliderRectangle->x = 0;
    m_colliderRectangle->y = 0;
    m_colliderRectangle->w = 100;
    m_colliderRectangle->h = 100;
}

Collider2D ::~Collider2D()
{
    delete m_colliderRectangle;
}

SDL_bool Collider2D::IsColliding(Collider2D &collider)
{
    if (m_colliderRectangle == nullptr)
        return SDL_FALSE;
    const SDL_Rect *temp = collider.m_colliderRectangle;
    if (temp == nullptr)
        return SDL_FALSE;
    return SDL_HasIntersection(m_colliderRectangle, temp);
}

void Collider2D::SetAbsolutePosition(int x, int y)
{
    m_colliderRectangle->x = x;
    m_colliderRectangle->y = y;
}

void Collider2D::SetDimensions(int w, int h)
{
    m_colliderRectangle->w = w;
    m_colliderRectangle->h = h;
}

int Collider2D::GetPositionX() {}
int Collider2D::GetPositionY() {}
int Collider2D::GetWidth() {}
int Collider2D::GetHeight() {}

SDL_Rect &Collider2D::GetColliderBoundingBox()
{
    return *m_colliderRectangle;
}