#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include <SDL2/SDL_image.h>

#include "texture.h"
#include "point.h"

class GameObject 
{
public:
    GameObject(Texture* t, const Point& pos);
    virtual ~GameObject();
    void draw(SDL_Renderer*);

protected:
    Texture* texture;
    double angle;
    SDL_Rect rect;
};

#endif
