
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "texture.h"

class User_Interface
{
public:
    User_Interface();
    User_Interface(Texture*);
    ~User_Interface();
    void draw(SDL_Renderer*);
    void update(int, bool);

private:
    TTF_Font* font;
    SDL_Color white;
    SDL_Texture* singularity_texture;
    SDL_Rect singularity_rect;
    bool has_singularity;
    int score;
};

#endif
