#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_image.h>

class Sprite 
{
public:
    Sprite();
    virtual void draw(SDL_Renderer*) const = 0;
    SDL_Rect getRect() const;

protected:
    struct Texture
    {
        SDL_Texture* texture;
        int width, height;
    };
    SDL_Rect rect;
    double angle;
};

#endif
