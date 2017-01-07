#include "Music.h"

using namespace std;

Music::Music(const string& path)
    : music{ Mix_LoadMUS(path.c_str()) }
{
    if (music == NULL)
    {
        throw "Could not load music " + path;
    }
}

Music::~Music()
{
    Mix_FreeMusic(music);
}

Mix_Music* Music::getMusic()
{
    return music;
}
