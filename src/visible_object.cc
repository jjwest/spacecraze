#include "../include/visible_object.h"

VisibleObject::VisibleObject(Texture* t, const Point& pos) 
    : texture{t}, angle{0}, rect{pos.x, pos.y, texture->getHeight(),
                                    texture->getWidth()} {}

VisibleObject::~VisibleObject() {}

void VisibleObject::draw(SDL_Renderer* renderer) const
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), &rect, 
                     NULL, angle, NULL, SDL_FLIP_NONE);
}
