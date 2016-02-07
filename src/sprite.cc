#include "../include/visible_object.h"

VisibleObject::VisibleObject() : angle{0} {}

void VisibleObject::draw(SDL_Renderer* renderer) const 
{
    SDL_RenderCopyEx(renderer, my_texture.texture, NULL, &rect,
                     angle, NULL, SDL_FLIP_NONE);
}

SDL_Rect VisibleObject::getRect() const 
{
    return rect;
}
