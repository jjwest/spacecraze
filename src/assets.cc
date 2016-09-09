#include "assets.h"

#include <stdexcept>
#include <string>

Assets& Assets::getInstance()
{
    return *instance;
}

void Assets::destroyInstance()
{
    delete instance;
    instance = nullptr;
}

Assets* Assets::instance(new Assets);

Texture* Assets::getTexture(const std::string& name) const
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

Mix_Music* Assets::getMusic(const std::string& name) const
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

TTF_Font* Assets::getFont(const std::string& name) const
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

void Assets::loadTexture(const std::string& name,
			       const std::string& path,
                               SDL_Renderer* renderer)
{
    textures.insert(make_pair(name, std::make_unique<Texture>(renderer, path)));
}

void Assets::loadMusic(const std::string& name, const std::string& path)
{
    music.insert(make_pair(name, std::make_unique<Music>(path)));
}

void Assets::loadFont(const std::string& name, const std::string& path, int size)
{
    fonts.insert(make_pair(name, std::make_unique<Font>(path, size)));
}
