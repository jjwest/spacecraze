#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_image.h>

#include "texture.h"

class Sprite {
public:
    Sprite(Texture*, int, int);
    void draw(SDL_Renderer*) const;
    SDL_Rect getRect() const;

protected:
    SDL_Texture* texture;
    SDL_Rect rect;
    double angle;
};

#endif
