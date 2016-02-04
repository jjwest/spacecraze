#include "../inc/asset_manager.h"
using namespace std;

AssetManager::AssetManager()
    : textures{}, music{}, fonts{} {}

AssetManager& AssetManager::getInstance() 
{
    static AssetManager instance;
    return instance;
}

AssetManager::~AssetManager()
{
    for (auto i : textures) 
    {
        delete i.second;
    }
    for (auto i : music) 
    {
        Mix_FreeMusic(i.second);
    }
    for (auto i : fonts) 
    {
        TTF_CloseFont(i.second);
    }
}

Texture* AssetManager::getTexture(const string& name) const 
{
    try
    {
        return textures.at(name);        
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
        return music.at(name);        
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
        return fonts.at(name);        
    }
    catch (exception& e)
    {
        throw "Tried to fetch non-loaded font " + name;
    }
}

void AssetManager::loadTexture(const string& name, const string& path, float scale,
                               SDL_Renderer* renderer) 
{   
    textures.insert( make_pair(name, new Texture(renderer, path, scale)) );
}

void AssetManager::loadMusic(const string& name, const string& path) 
{
    Mix_Music* loaded_music = Mix_LoadMUS(path.c_str());
    music.insert( make_pair(name, loaded_music) );
}

void AssetManager::loadFont(const string& name, const string& path, int size) 
{
    TTF_Font* loaded_font = TTF_OpenFont(path.c_str(), size);
    fonts.insert(make_pair(name, move(loaded_font)));
}

