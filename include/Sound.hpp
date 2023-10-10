#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL.h>
#include <string>

class ISound
{
public:
    virtual ~ISound() {}
    virtual void PlaySound() = 0;
    virtual void StopSound() = 0;
};

class Sound : public ISound
{
public:
    Sound(const std::string filepath);
    ~Sound();
    void PlaySound();
    void StopSound();
    void SetupDevice();

private:
    SDL_AudioDeviceID m_device;
    SDL_AudioSpec m_audioSpec;
    Uint8 *m_waveStart;
    Uint32 m_waveLength;
};

#endif