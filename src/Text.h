#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Point.h"

class Text
{
public:
    Text() = default;
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
    Text& operator=(Text&&) = default;
    ~Text();

    void draw(SDL_Renderer* renderer);
    void setText(const std::string& text);
    void setPosition(int x, int y);
    void setFont(TTF_Font* font);

private:
    SDL_Rect rect;
    SDL_Texture* texture = nullptr;
    TTF_Font* font = nullptr;
    bool render_new_texture = true;
    std::string text;
};


#endif // _TEXT_H_
