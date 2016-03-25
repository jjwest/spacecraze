#include "menu.h"

#include "asset_manager.h"

Menu::Menu(SDL_Renderer* renderer)
    : next_state{MENU}
{
    buttons.emplace_back(
        std::make_unique<Button>(renderer, 550, 400, "PLAY", PLAY));
    buttons.emplace_back(
        std::make_unique<Button>(renderer, 550, 450, "HIGHSCORE", HIGHSCORE));
    buttons.emplace_back(
        std::make_unique<Button>(renderer, 550, 500, "QUIT", QUIT));
}
      

void Menu::handleEvents()
{
    while (SDL_PollEvent(&events) != 0) {
        if (events.type == SDL_QUIT) {
            next_state = QUIT;
        }
        else if (events.type == SDL_MOUSEBUTTONDOWN) {
            update_buttons = true;
        }
    }
}

void Menu::update()
{
    if (update_buttons) {
        for (auto& button : buttons) {
            next_state = button->update(next_state);
        }
        update_buttons = false;
    }
}

void Menu::render(SDL_Renderer *renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    for (auto& button : buttons) {
        button->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

GameStates Menu::getNextState() const
{
    return next_state;
}
