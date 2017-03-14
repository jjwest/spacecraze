#include "GameObject.h"

Sprite::Sprite(Texture* texture, const SDL_Rect& hitbox)
    : texture{texture}, hitbox{hitbox} {}

Sprite::~Sprite() {}

void Sprite::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), NULL,
                     &hitbox, angle, NULL, SDL_FLIP_NONE);
}
