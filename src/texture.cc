#include "../inc/texture.h"

#include <SDL2/SDL_image.h>

Texture::Texture(SDL_Renderer* renderer, const std::string& path, float scale)
    : texture{nullptr}, width{0}, height{0}
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    width = surface->w * scale;
    height = surface->h * scale;;
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
