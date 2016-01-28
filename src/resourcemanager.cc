#include "../inc/resourcemanager.h"

#include <iostream>
#include <stdexcept>

using namespace std;

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager()  {
    for (auto t : textures) {
        delete t.second;
    }
    
    for (auto p : music) {
        Mix_FreeMusic(p.second);
    }

    for (auto it : fonts) {
        TTF_CloseFont(it.second);
    }
}

Texture* ResourceManager::getTexture(const string& name) const {
    return textures.at(name);
}

Mix_Music* ResourceManager::getMusic(const string& name) const {
    return music.at(name);
}

TTF_Font* ResourceManager::getFont(const string& name) const {
    return fonts.at(name);
}

void ResourceManager::loadTexture(const string& name, const string& path, float scale,
                                  SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        throw invalid_argument("Unable to load font " + path);
    }
    
    textures.insert({ name, new Texture(texture, surface->w, surface->h) });
    textures.at(name)->set_scale(scale);
                    
    SDL_FreeSurface(surface);
}

void ResourceManager::loadMusic(const string& name, const string& path) {
    Mix_Music* loaded_music = Mix_LoadMUS(path.c_str());
    
    if (loaded_music == NULL) {
        throw invalid_argument("Unable to load font " + path);
    }

    music.insert({ name, loaded_music });
}

void ResourceManager::loadFont(const string& name, const string& path, int size) {
    TTF_Font* font{ TTF_OpenFont(path.c_str(), size) };

    if (font == NULL) {
        throw invalid_argument("Unable to load font " + path);
    }

    fonts[name] = font;
}
