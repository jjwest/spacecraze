#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_image.h>

#include "texture.h"
#include "point.h"

class Sprite 
{
public:
    Sprite(Texture* t, const Point& pos);
    virtual ~Sprite();
    void draw(SDL_Renderer*);

protected:
    Texture* texture;
    double angle = 0;
    SDL_Rect rect;
};

#endif
