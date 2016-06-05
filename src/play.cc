#include "play.h"

#include "asset_manager.h"
#include "texture.h"
#include "world.h"

#include <iostream>

Play::Play(SDL_Renderer* renderer)
    : GameState(), world{renderer} {}
      

GameStates Play::getNextState() const
{
    return next_state;
}

int Play::getScore() const
{
    return world.getScore();
}

void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            next_state = QUIT;
        }
    }
}

void Play::update()
{
    enemy_generator.update(world);
    world.update();
    
    if (world.playerIsDead()) {
        next_state = MENU;
        std::cout << world.getScore() << '\n';
    }
}

void Play::render(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    world.render(renderer);
    SDL_RenderPresent(renderer);
}
