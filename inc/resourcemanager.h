#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

#include "texture.h"

class ResourceManager {
public:
    static ResourceManager& getInstance();
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;
    Texture* getTexture(const std::string&) const;
    Mix_Music* getMusic(const std::string&) const;
    TTF_Font* getFont(const std::string&) const;
    void loadTexture(const std::string&, const std::string&, float, SDL_Renderer*);
    void loadMusic(const std::string&, const std::string&);    
    void loadFont(const std::string&, const std::string&, int);

private:
    ResourceManager();
    std::map<std::string, Texture*> textures;
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, TTF_Font*> fonts;
};

#endif // _RESOURCEMANAGER_H_
