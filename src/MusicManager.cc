#include "MusicManager.h"

#include "AssetManager.h"

MusicManager::MusicManager()
{
    auto& assets = AssetManager::getInstance();
    music.insert( {"menu", assets.getMusic("menu")} );
    music.insert( {"play", assets.getMusic("play")} );
}

void MusicManager::start()
{
    Mix_PlayMusic(music.at("menu"), -1);
}

void MusicManager::update(State current_state)
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

bool MusicManager::switchingToPlay(State current_state) const
{
    return current_music != current_state && current_state == State::PLAY;
}

bool MusicManager::switchingFromPlay(State current_state) const
{
    return current_music != current_state && current_music == State::PLAY;
}
