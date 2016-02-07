#include "../inc/visible_object.h"

VisibleObject::VisibleObject(Texture* t, int x, int y) 
    : texture{t}, angle{0}, rect{x, y, texture->getHeight(), 
                                       texture->getWidth()} {}

SDL_Rect VisibleObject::getRect() const 
{
    return rect;
}

void VisibleObject::draw(SDL_Renderer* renderer) const
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), &rect, 
                     NULL, angle, NULL, SDL_FLIP_NONE);
}
