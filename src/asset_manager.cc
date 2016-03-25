#include "asset_manager.h"

#include <stdexcept>
#include <string>

AssetManager& AssetManager::getInstance() 
{
    return *instance;
}

void AssetManager::destroyInstance()
{
    delete instance;
    instance = nullptr;
}

AssetManager* AssetManager::instance(new AssetManager);

Texture* AssetManager::getTexture(const std::string& name) const 
{
    try {
        return &*textures.at(name);        
    }
    catch (std::exception& e) {
        throw std::invalid_argument("Tried to fetch non-loaded texture " + name);
    }
}

Mix_Music* AssetManager::getMusic(const std::string& name) const 
{
    try {
        return music.at(name)->getMusic();
    }
    catch (std::exception& e) {
        throw std::invalid_argument("Tried to fetch non-loaded music " + name);
    }
}

TTF_Font* AssetManager::getFont(const std::string& name) const 
{
    try {
        return fonts.at(name)->getFont();        
    }
    catch (std::exception& e) {
        throw std::invalid_argument("Tried to fetch non-loaded font " + name);
    }
}

void AssetManager::loadTexture(const std::string& name, const std::string& path, float scale,
                               SDL_Renderer* renderer) 
{   
    textures.insert(make_pair(name, std::make_unique<Texture>(renderer,
                                                               path,
                                                               scale)));
}

void AssetManager::loadMusic(const std::string& name, const std::string& path) 
{
    music.insert(make_pair(name, std::make_unique<Music>(path)));
}

void AssetManager::loadFont(const std::string& name, const std::string& path, int size)
{
    fonts.insert(make_pair(name, std::make_unique<Font>(path, size)));
}
