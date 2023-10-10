#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "TextureRectangle.hpp"
#include "Collider2D.hpp"

class GameObject
{
public:
    GameObject();
    GameObject(SDL_Renderer *renderer, std::string spritepath);
    ~GameObject();
    void Update();
    void Render();
    TextureRectangle &GetSprite();
    Collider2D &GetCollider2D();

private:
    TextureRectangle *m_sprite;
    SDL_Renderer *m_renderer;
    Collider2D *m_collider;
};

#endif