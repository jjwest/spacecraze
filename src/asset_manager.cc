#include "../inc/asset_manager.h"
#include <iostream>
using namespace std;

AssetManager::AssetManager()
    : textures{}, music{}, fonts{} {}

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

Texture* AssetManager::getTexture(const string& name) const 
{
    try
    {
        return &*textures.at(name);        
    }
    catch (exception& e)
    {
        throw "Tried to fetch non-loaded texture " + name;
    }
}

Mix_Music* AssetManager::getMusic(const string& name) const 
{
    try
    {
        return music.at(name)->getMusic();
    }
    catch (exception& e)
    {
        throw "Tried to fetch non-loaded music " + name;
    }
}

TTF_Font* AssetManager::getFont(const string& name) const 
{
    try
    {
        return fonts.at(name)->getFont();        
    }
    catch (exception& e)
    {
        throw "Tried to fetch non-loaded font " + name;
    }
}

void AssetManager::loadTexture(const string& name, const string& path, float scale,
                               SDL_Renderer* renderer) 
{   
    unique_ptr<Texture> loaded_texture { new Texture(renderer, path, scale) };
    textures.insert(make_pair( name, move(loaded_texture) ));
}

void AssetManager::loadMusic(const string& name, const string& path) 
{
    unique_ptr<Music> loaded_music { new Music(path) };
    music.insert(make_pair( name, move(loaded_music) ));
}

void AssetManager::loadFont(const string& name, const string& path, int size)
{
    unique_ptr<Font> loaded_font { new Font(path, size) };
    fonts.insert(make_pair( name, move(loaded_font) ));
}
