#include "Button.h"

#include "AssetManager.h"

Button::~Button()
{
    SDL_DestroyTexture(texture_normal);
    SDL_DestroyTexture(texture_highlighted);
}

bool Button::mouseOver() const
{
    Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    return (mouse.x >= rect.x &&
	    mouse.x <= rect.x + rect.w &&
	    mouse.y >= rect.y &&
	    mouse.y <= rect.y + rect.h);
}

void Button::draw(SDL_Renderer* renderer)
{
    if (text_modified)
    {
	SDL_DestroyTexture(texture_normal);
	SDL_DestroyTexture(texture_highlighted);

	auto font = AssetManager::instance().getFont("text");

	SDL_Color color_normal = {255, 255, 255, 0};
	auto surface_normal = TTF_RenderText_Solid(font, text.c_str(), color_normal);
	texture_normal = SDL_CreateTextureFromSurface(renderer, surface_normal);
	rect.w = surface_normal->w;
	rect.h = surface_normal->h;
	SDL_FreeSurface(surface_normal);

	SDL_Color color_highlighted = {0, 255, 0, 0};
	auto surface_highlighted = TTF_RenderText_Solid(font, text.c_str(), color_highlighted);
	texture_highlighted = SDL_CreateTextureFromSurface(renderer, surface_highlighted);
	SDL_FreeSurface(surface_highlighted);

	text_modified = false;
    }

    if (highlighted)
    {
        SDL_RenderCopy(renderer, texture_highlighted, NULL, &rect);
    }
    else
    {
        SDL_RenderCopy(renderer, texture_normal, NULL, &rect);
    }
}

void Button::setText(const std::string& text)
{
    this->text = text;
    text_modified = true;
}

void Button::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Button::addHighlight()
{
    highlighted = true;
}

void Button::removeHighlight()
{
    highlighted = false;
}
