#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <memory>

#include "texture.h"
#include "font.h"
#include "music.h"

class AssetManager 
{
public:
    static AssetManager& getInstance();
    static void destroyInstance();
    AssetManager(const AssetManager&) = delete;
    void operator=(const AssetManager&) = delete;

    Mix_Music* getMusic(const std::string& name) const;
    Texture* getTexture(const std::string& name) const;
    TTF_Font* getFont(const std::string& name) const;
    void loadTexture(const std::string& name, const std::string& path,
                     float scale, SDL_Renderer*);
    void loadMusic(const std::string& name, const std::string& path);    
    void loadFont(const std::string& name, const std::string& path, int size);

private:
    AssetManager();
    static AssetManager* instance;
    std::map<std::string, std::unique_ptr<Texture>> textures;
    std::map<std::string, std::unique_ptr<Music>> music;
    std::map<std::string, std::unique_ptr<Font>> fonts;
};

#endif // _ASSET_MANAGER_H_
