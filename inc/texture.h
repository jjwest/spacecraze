#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
public:
    Texture(SDL_Texture*, int, int);
    ~Texture();
    SDL_Texture* getTexture() const;
    int getWidth() const;
    int getHeight() const;
    void setScale(float);

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif
