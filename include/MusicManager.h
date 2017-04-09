#ifndef _MUSIC_MANAGER_H_
#define _MUSIC_MANAGER_H_

#include <SDL2/SDL_mixer.h>
#include <unordered_map>

#include "Enums.h"

class MusicManager
{
public:
    MusicManager();
    void start();
    void update(State current_state);

private:
    State current_music = State::MENU;
    std::unordered_map<std::string, Mix_Music*> music;

    bool switchingToPlay(State current_state) const;
    bool switchingFromPlay(State current_state) const;
};


#endif // _MUSIC_MANAGER_H_
