#include "../inc/sprite.h"

Sprite::Sprite(Texture* t, int x, int y) 
    : angle{0} {
    texture = t->getTexture();
    rect.x = x;
    rect.y = y;
    rect.w = t->getWidth();
    rect.h = t->getHeight();
}

void Sprite::draw(SDL_Renderer* renderer) const {
    SDL_RenderCopyEx(renderer, texture, NULL, &rect,
                     angle, NULL, SDL_FLIP_NONE);
}

SDL_Rect Sprite::getRect() const {
    return rect;
}
