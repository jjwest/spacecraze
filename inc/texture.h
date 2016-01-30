#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

struct Texture
{
    Texture(std::string const& path, SDL_Renderer* renderer);
    ~Texture();
    SDL_Texture* texture;
    int width;
    int sheight;
};

#endif
