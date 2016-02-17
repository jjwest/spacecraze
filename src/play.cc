#include "../include/play.h"

#include "../include/asset_manager.h"
#include "../include/texture.h"

Play::Play()
    : GameState(), next_state{PLAY} {}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) 
        {
            next_state = QUIT;
        }
    }
}

void Play::update()
{
    enemy_generator.update(world);
    world.update();
}

void Play::render(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto& assets = AssetManager::getInstance();
    auto background = assets.getTexture("background")->getTexture();
    SDL_RenderCopy(renderer, background, NULL, NULL);
    world.render(renderer);
    SDL_RenderPresent(renderer);
}

GameStates Play::getNextState() const
{
    return next_state;
}

