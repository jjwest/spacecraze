#include "game_object.h"

Sprite::Sprite(Texture* t, const SDL_Rect& r)
    : texture{t}, rect{r} {}

Sprite::~Sprite() {}

void Sprite::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), NULL,
                     &rect, angle, NULL, SDL_FLIP_NONE);
}
