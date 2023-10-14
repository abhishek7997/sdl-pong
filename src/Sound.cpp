#include "Sound.hpp"
#include <iostream>

Sound::Sound(const std::string filepath)
{
    if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr)
    {
        std::cerr << "Sound loading error: " << SDL_GetError() << std::endl;
    }
}

Sound::~Sound()
{
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound()
{
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    if (status < 0)
    {
        std::cout << "Could not play sound: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_PauseAudioDevice(m_device, 0);
}

void Sound::StopSound()
{
    SDL_PauseAudioDevice(m_device, 1);
}

void Sound::SetupDevice()
{
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (m_device == 0)
    {
        std::cout << "Sound device error: " << SDL_GetError() << std::endl;
    }
}
