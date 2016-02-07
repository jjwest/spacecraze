#include "../include/user_interface.h"

#include <iostream>

User_Interface::User_Interface()
    : font{nullptr}, singularity_texture{nullptr}, has_singularity{true} {}

User_Interface::User_Interface(Texture* s)
    : has_singularity{true}, score{0}
{
    singularity_texture = s->get_texture();
    singularity_rect.x = 875;
    singularity_rect.y = 85;
    singularity_rect.w = s->get_width();
    singularity_rect.h = s->get_height();

    font = TTF_OpenFont("Akashi.ttf", 24);
    if( font == NULL )
    {
        std::cerr << "Failed to load font. Reason: " 
                  << TTF_GetError() << std::endl;
        exit(1);
    }

    white = {255, 255, 255, 255};
}

User_Interface::~User_Interface()
{
    TTF_CloseFont(font);
}

void User_Interface::draw(SDL_Renderer* renderer)
{
    std::string score_text{ "Score: " + std::to_string(score) };
    SDL_Surface* surface = TTF_RenderText_Solid(font, score_text.c_str(), white);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect message_rect;
    message_rect.x = 850;
    message_rect.y = 50;
    message_rect.w = surface->w;
    message_rect.h = surface->h;
    
    SDL_RenderCopy(renderer, message, NULL, &message_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);

    if( has_singularity )
    {
        SDL_RenderCopy(renderer, singularity_texture, NULL, &singularity_rect);
    }
}

void User_Interface::update(int s, bool singularity)
{
    score = s;
    has_singularity = singularity;
}


