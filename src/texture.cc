#include "../inc/texture.h"

Texture::Texture(SDL_Texture* t, int w, int h)
    : texture{t}, width{w}, height{h} {}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

void Texture::setScale(float scale) {
    width = static_cast<int>(width * scale);
    height = static_cast<int>(height * scale);    
}

