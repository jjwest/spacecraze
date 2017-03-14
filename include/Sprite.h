#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_image.h>

#include "Texture.h"
#include "Point.h"

class Sprite
{
public:
    Sprite(Texture* texture, const SDL_Rect& hitbox);
    virtual ~Sprite();
    void draw(SDL_Renderer* renderer);

protected:
    Texture* texture;
    double angle = 0;
    SDL_Rect hitbox;
};

#endif
