#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include <SDL2/SDL_image.h>

#include "texture.h"

class VisibleObject 
{
public:
    VisibleObject(Texture* t, int x, int y);
    virtual ~VisibleObject();
    SDL_Rect getRect() const;
    void draw(SDL_Renderer*) const;

protected:
    Texture* texture;
    double angle;
    SDL_Rect rect;
};

#endif
