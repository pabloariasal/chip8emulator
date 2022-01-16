// Taken from: https://stackoverflow.com/a/54618912/4289533
#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

class Sound
{
public:
    Sound();
    ~Sound();
    void play();
    void stop();

private:
    const double m_sineFreq;
    const double m_sampleFreq;
    const double m_samplesPerSine;
    uint32_t m_samplePos;

    static void SDLAudioCallback(void *data, Uint8 *buffer, int length);

    SDL_AudioDeviceID m_device;
};
