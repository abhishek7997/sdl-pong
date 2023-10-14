#include "GameObject.hpp"

GameObject::GameObject()
{
    m_sprite = nullptr;
    m_collider = nullptr;
}
GameObject::GameObject(SDL_Renderer *renderer, std::string spritepath)
{
    m_renderer = renderer;
    m_sprite = new TextureRectangle(m_renderer, spritepath);
    m_collider = new Collider2D();
}

GameObject ::~GameObject()
{
    if (m_sprite != nullptr)
        delete m_sprite;
    if (m_collider != nullptr)
        delete m_collider;
}

void GameObject::Update()
{
    if (m_sprite != nullptr && m_collider != nullptr)
    {
        int x = m_sprite->GetPositionX();
        int y = m_sprite->GetPositionY();
        int w = m_sprite->GetWidth();
        int h = m_sprite->GetHeight();
        m_collider->SetAbsolutePosition(x, y);
        m_collider->SetDimensions(w, h);
    }
}

void GameObject::Render()
{
    if (m_sprite != nullptr)
        m_sprite->Render(m_renderer);
    // if (m_collider != nullptr)
    // {
    //     SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
    //     SDL_RenderDrawRect(m_renderer, &m_collider->GetColliderBoundingBox());
    // }
}

TextureRectangle &GameObject::GetSprite()
{
    return *m_sprite;
}
Collider2D &GameObject::GetCollider2D()
{
    return *m_collider;
}