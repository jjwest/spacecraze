#include "highscore.h"
#include "asset_manager.h"
#include "point.h"

Highscore::Highscore(SDL_Renderer* renderer)
    : button_back{ renderer, {450, 850}, "BACK", MENU },
      title{renderer,
              "HIGHSCORE",
              {450, 200},
              AssetManager::getInstance().getFont("title"),
              {255, 255, 255, 255} }
{
    
}

GameStates Highscore::getNextState() const
{
    return next_state;
}

void Highscore::handleEvents()
{
    while (SDL_PollEvent(&events) != 0) {
        if (events.type == SDL_QUIT) {
            next_state = QUIT;
        }
        else if (events.type == SDL_MOUSEBUTTONDOWN) {
            checkButtonPressed();
        }
    }
}

void Highscore::update() {}

void Highscore::render(SDL_Renderer* renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    
}

void Highscore::checkButtonPressed()
{
    next_state = button_back.update(next_state);
}
