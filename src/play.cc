#include "play.h"

#include "asset_manager.h"
#include "texture.h"
#include "world.h"

Play::Play() : GameState(), next_state{PLAY}
{
    world.reset(new World());
}
      

GameStates Play::getNextState() const
{
    return next_state;
}

void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) 
        {
            setNextState(QUIT);
        }
    }
}

void Play::update()
{
    enemy_generator.update(*world);
    world->update();

    if (world->playerDead()) 
    {
        setNextState(QUIT);
    }
}

void Play::render(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto& assets = AssetManager::getInstance();
    auto background = assets.getTexture("background")->getTexture();
    SDL_RenderCopy(renderer, background, NULL, NULL);
    world->render(renderer);
    SDL_RenderPresent(renderer);
}

void Play::setNextState(GameStates state)
{
    if (next_state != QUIT) 
    {
        next_state = state;
    }
}
