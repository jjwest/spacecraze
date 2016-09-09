#include "play.h"

#include "assets.h"
#include "texture.h"
#include "world.h"

#include <iostream>

Play::Play(SDL_Renderer* renderer)
    : GameState(), user_interface{renderer} {}


States Play::getNextState() const
{
    return next_state;
}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State_Quit;
        }
    }
}

void Play::update()
{
    enemy_generator.update(world);
    current_score += world.update();

    if (world.playerIsDead())
    {
        next_state = State_Menu;
    }
}

void Play::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto background = Assets::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    world.draw(renderer);
    SDL_RenderPresent(renderer);
}
