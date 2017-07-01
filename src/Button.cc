#include "Button.h"

#include "AssetManager.h"

Button::~Button()
{
    SDL_DestroyTexture(texture_normal);
    SDL_DestroyTexture(texture_hover);
}

bool Button::mouseOver() const
{
    Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    return mouse.x >= rect.x
	&& mouse.x <= rect.x + rect.w
	&& mouse.y >= rect.y
	&& mouse.y <= rect.y + rect.h;
}

void Button::draw(SDL_Renderer* renderer)
{
    if (text_modified)
    {
	SDL_DestroyTexture(texture_normal);
	SDL_DestroyTexture(texture_hover);

	auto font = AssetManager::getInstance().getFont("text");
	SDL_Color color_normal = {255, 255, 255, 0};
	SDL_Color color_hover = {0, 255, 0, 0};

	auto normal_surface = TTF_RenderText_Solid(font, text.c_str(), color_normal);
	rect.w = normal_surface->w;
	rect.h = normal_surface->h;
	texture_normal = SDL_CreateTextureFromSurface(renderer, normal_surface);
	SDL_FreeSurface(normal_surface);

	auto hover_surface = TTF_RenderText_Solid(font, text.c_str(), color_hover);
	texture_hover = SDL_CreateTextureFromSurface(renderer, hover_surface);
	SDL_FreeSurface(hover_surface);

	text_modified = false;
    }

    if (highlighted)
    {
        SDL_RenderCopy(renderer, texture_hover, NULL, &rect);
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
