#include "Text.h"
#include "AssetManager.h"

Text::Text(SDL_Renderer* renderer, const std::string& text,
                           const Point& pos, TTF_Font* font)
{
    SDL_Color white{ 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
}

Text::~Text()
{
    SDL_DestroyTexture(texture);
}

void Text::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
