#include "music_manager.h"

#include "assets.h"

MusicManager::MusicManager()
{
    auto& assets = Assets::getInstance();
    music.insert({ "menu", assets.getMusic("menu")});
    music.insert({ "play", assets.getMusic("play")});

    Mix_PlayMusic(music.at("menu"), -1);
}

void MusicManager::update(States current_state)
{
    if (switchingToPlay(current_state))
    {
	Mix_PlayMusic(music.at("play"), -1);
    }
    else if (switchingFromPlay(current_state))
    {
	Mix_PlayMusic(music.at("menu"), -1);
    }

    current_music = current_state;
}

bool MusicManager::switchingToPlay(States current_state) const
{
    return current_music != current_state && current_state == State_Play;
}

bool MusicManager::switchingFromPlay(States current_state) const
{
    return current_music != current_state && current_music == State_Play;
}
