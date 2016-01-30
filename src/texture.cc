#include "../inc/texture.h"

#include <stderr>

using namespace std;

Texture::Texture(string const& path, SDL_Renderer* renderer)
{
    SDL_Surface*  surface = Load_IMG(path.c_str());
    if (surface == NULL) {
        throw invalid_argument("Could not load sprite: " + path);
    }
        
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}
