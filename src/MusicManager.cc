#include "MusicManager.h"

#include "AssetManager.h"
#include "Globals.h"

MusicManager::MusicManager()
{
    auto& assets = AssetManager::instance();
    music.insert( {"menu", assets.getMusic("menu")} );
    music.insert( {"play", assets.getMusic("play")} );
}

void MusicManager::start()
{
    Mix_PlayMusic(music.at("menu"), -1);
}

void MusicManager::update(State current_state)
{
    if (GLOBAL_SETTINGS.music)
    {
		if (shouldStartPlayMusic(current_state))
		{
			Mix_PlayMusic(music.at("play"), -1);
			current_music = State::PLAY;
		}
		else if (shouldStartMenuMusic(current_state))
		{
			Mix_PlayMusic(music.at("menu"), -1);
			current_music = State::MENU;
		}
    }
    else
    {
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
			current_music = State::QUIT;
		}
    }
}

bool MusicManager::shouldStartPlayMusic(State current_state) const
{
    return current_music != current_state && current_state == State::PLAY;
}

bool MusicManager::shouldStartMenuMusic(State current_state) const
{
    return current_music != State::MENU && current_state != State::PLAY;
}
