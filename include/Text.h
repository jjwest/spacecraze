#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Point.h"

class Text
{
public:
    Text(SDL_Renderer* renderer, const std::string& text,
                 const Point& pos, TTF_Font* font);
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
    Text& operator=(Text&&) = default;
    ~Text();

    void draw(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Texture* texture;
};


#endif // _TEXT_H_
