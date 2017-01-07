#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <SDL2/SDL_mixer.h>
#include <string>

class Music
{
public:
    Music(const std::string& path);
    Music(const Music&) = delete;    
    Music& operator=(const Music&) = delete;
    ~Music();    
    Mix_Music* getMusic();

private:
    Mix_Music* music;
};


#endif // _MUSIC_H_
