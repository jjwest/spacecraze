#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include <SDL2/SDL_image.h>

#include "texture.h"
#include "point.h"

class VisibleObject 
{
public:
    VisibleObject(Texture* t, const Point& pos);
    virtual ~VisibleObject();
    void draw(SDL_Renderer*) const;

protected:
    Texture* texture;
    double angle;
    SDL_Rect rect;
};

#endif
