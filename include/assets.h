#ifndef _ASSETS_H_
#define _ASSETS_H_

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

class Assets
{
public:
    Assets(const Assets&) = delete;
    Assets(Assets&&) = delete;
    void operator=(const Assets&) = delete;
    void operator=(Assets&&) = delete;
    static Assets& getInstance();
    static void destroyInstance();

    Mix_Music* getMusic(const std::string& name) const;
    Texture* getTexture(const std::string& name) const;
    TTF_Font* getFont(const std::string& name) const;
    void loadTexture(const std::string& name, const std::string& path,
                     SDL_Renderer* renderer);
    void loadMusic(const std::string& name, const std::string& path);
    void loadFont(const std::string& name, const std::string& path, int size);

private:
    Assets() = default;
    static Assets* instance;
    std::map<std::string, std::unique_ptr<Texture>> textures;
    std::map<std::string, std::unique_ptr<Music>> music;
    std::map<std::string, std::unique_ptr<Font>> fonts;
};

#endif // _ASSETS_H_
