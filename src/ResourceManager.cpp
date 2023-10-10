#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
}

ResourceManager::ResourceManager(ResourceManager const &)
{
}

ResourceManager ResourceManager::operator=(ResourceManager const &)
{
    return *this;
}

ResourceManager &ResourceManager::GetInstance()
{
    static ResourceManager *s_instance = new ResourceManager();
    return *s_instance;
}

SDL_Surface *ResourceManager::GetSurface(std::string filepath)
{
    auto search = m_surfaces.find(filepath);

    if (search == m_surfaces.end())
    {
        SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath, surface));
    }

    return m_surfaces[filepath];
}