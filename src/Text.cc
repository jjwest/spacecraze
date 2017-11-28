#include "Text.h"
#include "AssetManager.h"

Text::~Text()
{
    SDL_DestroyTexture(texture);
}

void Text::draw(SDL_Renderer *renderer)
{
    if (render_new_texture && font != nullptr)
    {
		SDL_Color white{ 255, 255, 255, 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		rect.w = surface->w;
		rect.h = surface->h;
		SDL_FreeSurface(surface);
    }
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::setText(const std::string& text)
{
    this->text = text;
}

void Text::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Text::setFont(TTF_Font* font)
{
    this->font = font;
}
