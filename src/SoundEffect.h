#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

class SoundEffect
{
public:
    SoundEffect(const std::string& path);
    SoundEffect(const SoundEffect&) = delete;
    SoundEffect& operator=(const SoundEffect&) = delete;
    ~SoundEffect();
    Mix_Chunk* getSound() const;

private:
    Mix_Chunk* sound;
};


#endif // _SOUNDEFFECT_H_
