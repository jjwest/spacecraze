#include "AssetManager.h"
#include "Globals.h"

#include <stdexcept>
#include <string>

std::string parseProjectRoot()
{
    std::string current_path = __FILE__;
    std::string project_name = "spacecraze";
    auto pos = current_path.find(project_name);
    if (pos == current_path.npos)
    {
	throw std::runtime_error("Could not parse project root");
    }

    current_path.erase(
	current_path.begin() + pos + project_name.size(),
	current_path.end()
    );

    return current_path;
}



AssetManager& AssetManager::instance()
{
    return *instance_;
}

void AssetManager::destroyInstance()
{
    delete instance_;
    instance_ = nullptr;
}

AssetManager* AssetManager::instance_(new AssetManager);

void AssetManager::initialize()
{
    auto root = parseProjectRoot();
    texture_path = root + "/assets/sprites/";
    music_path = root + "/assets/music/";
    font_path = root + "/assets/fonts/";
    sound_path = root + "/assets/sounds/";
}

Texture* AssetManager::getTexture(const std::string& name) const
{
    try
    {
        return &*textures.at(name);
    }
    catch (std::exception& e)
    {
        throw std::invalid_argument("Tried to fetch non-loaded texture " + name);
    }
}

Mix_Music* AssetManager::getMusic(const std::string& name) const
{
    try
    {
        return music.at(name)->getMusic();
    }
    catch (std::exception& e)
    {
        throw std::invalid_argument("Tried to fetch non-loaded music " + name);
    }
}

TTF_Font* AssetManager::getFont(const std::string& name) const
{
    try
    {
        return fonts.at(name)->getFont();
    }
    catch (std::exception& e)
    {
        throw std::invalid_argument("Tried to fetch non-loaded font " + name);
    }
}

Mix_Chunk* AssetManager::getSoundEffect(const std::string& name) const
{
    try
    {
        return sounds.at(name)->getSound();
    }
    catch (std::exception& e)
    {
        throw std::invalid_argument("Tried to fetch non-loaded music " + name);
    }
}

void AssetManager::loadTexture(const std::string& name,
			       const std::string& path,
                               SDL_Renderer* renderer)
{
    textures.insert(
	make_pair(
	    name,
	    std::make_unique<Texture>(renderer, texture_path + path)
	    )
	);
}

void AssetManager::loadMusic(const std::string& name, const std::string& file_name)
{
    music.insert(make_pair(name, std::make_unique<Music>(music_path + file_name)));
}

void AssetManager::loadFont(const std::string& name, const std::string& file_name, int size)
{
    fonts.insert(make_pair(name, std::make_unique<Font>(font_path + file_name, size)));
}

void AssetManager::loadSoundEffect(const std::string& name, const std::string& file_name)
{
    sounds.insert(make_pair(name, std::make_unique<SoundEffect>(sound_path + file_name)));
}
