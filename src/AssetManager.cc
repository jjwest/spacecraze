#include "AssetManager.h"
#include "Globals.h"

#include <stdexcept>
#include <string>

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

void AssetManager::setProjectRoot(const std::string& project_root)
{
    asset_root = project_root + "/assets/";
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
	    std::make_unique<Texture>(renderer, asset_root + path)
	    )
	);
}

void AssetManager::loadMusic(const std::string& name, const std::string& path)
{
    music.insert(make_pair(name, std::make_unique<Music>(asset_root + path)));
}

void AssetManager::loadFont(const std::string& name, const std::string& path, int size)
{
    fonts.insert(make_pair(name, std::make_unique<Font>(asset_root + path, size)));
}

void AssetManager::loadSoundEffect(const std::string& name, const std::string& path)
{
    sounds.insert(make_pair(name, std::make_unique<SoundEffect>(asset_root + path)));
}
