#include "play.h"

#include "asset_manager.h"
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
    world.update(current_score);

    if (world.playerIsDead())
    {
        next_state = State_Menu;
        std::cout << current_score.getScore() << std::endl;
    }
}

void Play::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    world.draw(renderer);
    SDL_RenderPresent(renderer);
}
