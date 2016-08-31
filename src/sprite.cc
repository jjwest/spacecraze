#include "game_object.h"

Sprite::Sprite(Texture* t, const Point& pos)
    : texture{t}, rect{pos.x, pos.y, texture->getWidth(),
                                    texture->getHeight()} {}

Sprite::~Sprite() {}

void Sprite::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), NULL,
                     &rect, angle, NULL, SDL_FLIP_NONE);
}
