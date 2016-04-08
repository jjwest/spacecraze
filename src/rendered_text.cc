#include "rendered_text.h"

RenderedText::RenderedText(SDL_Renderer* renderer, const std::string& text,
                           const Point& pos, TTF_Font* font,
                           const SDL_Color& color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
    
}

RenderedText::~RenderedText()
{
    SDL_DestroyTexture(texture);
}

void RenderedText::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
