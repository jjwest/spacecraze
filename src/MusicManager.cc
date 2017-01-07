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
