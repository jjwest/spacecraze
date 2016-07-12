#include "button.h"

#include <iostream>

#include "asset_manager.h"

Button::Button(SDL_Renderer* renderer, const Point& pos, const std::string& text,
               const State& act)
    : action{act}
{
    rect.x = pos.x;
    rect.y = pos.y;
    
    auto font = AssetManager::getInstance().getFont("button");
    SDL_Color color_normal = {255, 255, 255, 0};
    SDL_Color color_hover = {0, 255, 0, 0};
    
    auto normal_surface = TTF_RenderText_Solid(font, text.c_str(), color_normal);
    rect.w = normal_surface->w;
    rect.h = normal_surface->h;
    normal = SDL_CreateTextureFromSurface(renderer, normal_surface);
    SDL_FreeSurface(normal_surface);
    
    auto hover_surface = TTF_RenderText_Solid(font, text.c_str(), color_hover);
    hover = SDL_CreateTextureFromSurface(renderer, hover_surface);
    SDL_FreeSurface(hover_surface);
}

Button::~Button()
{
    SDL_DestroyTexture(normal);
    SDL_DestroyTexture(hover);
}

State Button::update(const State& current_state)
{
    return mouseOverButton() ? action : current_state;
}

void Button::draw(SDL_Renderer* renderer)
{
    if (mouseOverButton()) {
        SDL_RenderCopy(renderer, hover, NULL, &rect);
    }
    else {
        SDL_RenderCopy(renderer, normal, NULL, &rect);
    }
}

bool Button::mouseOverButton() const
{
    Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    return mouse.x >= rect.x
        && mouse.x <= rect.x + rect.w
        && mouse.y >= rect.y
        && mouse.y <= rect.y + rect.h;
}
