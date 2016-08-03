#include "texture.h"

#include <SDL2/SDL_image.h>
#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const std::string& path)
    : texture{nullptr}, width{0}, height{0}
{
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == NULL)
    {
        throw "Could not find texture " + path;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const
{
    return texture;
}

int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}
