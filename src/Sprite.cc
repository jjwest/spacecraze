#include "GameObject.h"

Sprite::Sprite(Texture* t, const SDL_Rect& r)
    : texture{t}, hitbox{r} {}

Sprite::~Sprite() {}

void Sprite::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), NULL,
                     &hitbox, angle, NULL, SDL_FLIP_NONE);
}
