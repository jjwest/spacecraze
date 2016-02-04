#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include <SDL2/SDL_image.h>

class VisibleObject 
{
public:
    VisibleObject();
    virtual ~VisibleObject();
    virtual void draw(SDL_Renderer*) const = 0;
    SDL_Rect getRect() const;

protected:
    SDL_Rect rect;
    double angle;
};

#endif
