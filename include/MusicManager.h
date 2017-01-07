#ifndef _MUSIC_MANAGER_H_
#define _MUSIC_MANAGER_H_

#include <SDL2/SDL_mixer.h>
#include <map>

#include "Enums.h"

class MusicManager
{
public:
    MusicManager();
    void start();
    void update(States current_state);

private:
    States current_music = State_Menu;
    std::map<std::string, Mix_Music*> music;

    bool switchingToPlay(States current_state) const;
    bool switchingFromPlay(States current_state) const;
};


#endif // _MUSIC_MANAGER_H_
