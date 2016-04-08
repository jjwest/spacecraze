#ifndef _RENDERED_TEXT_H_
#define _RENDERED_TEXT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "point.h"

class RenderedText
{
public:
    RenderedText(SDL_Renderer* renderer, const std::string& text,
                 const Point& pos, TTF_Font* font, const SDL_Color& color);
    RenderedText(const RenderedText&) = delete;
    RenderedText(RenderedText&&) = default;
    RenderedText& operator=(const RenderedText&) = delete;
    RenderedText& operator=(RenderedText&&) = default;
    ~RenderedText();
    
    void draw(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Texture* texture;
};


#endif // _RENDERED_TEXT_H_
