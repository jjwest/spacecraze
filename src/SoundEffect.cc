#include "SoundEffect.h"

SoundEffect::SoundEffect(const std::string& path)
    : sound{ Mix_LoadWAV(path.c_str())}
{
    if (sound == NULL)
    {
        throw "Could not load sound effect " + path;
    }
}

SoundEffect::~SoundEffect()
{
    Mix_FreeChunk(sound);
}

Mix_Chunk* SoundEffect::getSound() const
{
    return sound;
}
