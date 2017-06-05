#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <memory>
#include <string>

#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"
#include "Texture.h"

class AssetManager
{
public:
    AssetManager(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    void operator=(const AssetManager&) = delete;
    void operator=(AssetManager&&) = delete;
    static AssetManager& getInstance();
    static void destroyInstance();

    Mix_Music* getMusic(const std::string& name) const;
    Texture* getTexture(const std::string& name) const;
    TTF_Font* getFont(const std::string& name) const;
    Mix_Chunk* getSoundEffect(const std::string& name) const;
    void loadTexture(const std::string& name, const std::string& path, SDL_Renderer* renderer);
    void loadMusic(const std::string& name, const std::string& path);
    void loadFont(const std::string& name, const std::string& path, int size);
    void loadSoundEffect(const std::string& name, const std::string& path);

private:
    AssetManager() = default;
    static AssetManager* instance;
    std::map<std::string, std::unique_ptr<Texture>> textures;
    std::map<std::string, std::unique_ptr<Music>> music;
    std::map<std::string, std::unique_ptr<Font>> fonts;
    std::map<std::string, std::unique_ptr<SoundEffect>> sounds;
};

#endif // _ASSETS_H_
