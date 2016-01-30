#include "../inc/visible_object.h"

VisibleObject::VisibleObject() : angle{0} {}

SDL_Rect VisibleObject::getRect() const 
{
    return rect;
}
