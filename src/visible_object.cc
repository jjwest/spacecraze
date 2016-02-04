#include "../inc/visible_object.h"

VisibleObject::VisibleObject() : rect{1, 1, 1, 1}, angle{0} {}

VisibleObject::~VisibleObject() {}

SDL_Rect VisibleObject::getRect() const 
{
    return rect;
}

