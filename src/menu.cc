#include "menu.h"
#include "asset_manager.h"
#include "point.h"

Menu::Menu(SDL_Renderer* renderer)
    : next_state{State_Menu},
      title{ renderer,
              "SPACECRAZE",
              {450, 150},
              AssetManager::getInstance().getFont("title")}
{
    buttons.emplace_back(
        std::make_unique<Button>(renderer, Point{550, 400}, "PLAY", State_Play));
    buttons.emplace_back(
        std::make_unique<Button>(renderer, Point{550, 450}, "HIGHSCORE", State_ViewHighscore));
    buttons.emplace_back(
        std::make_unique<Button>(renderer, Point{550, 500}, "QUIT", State_Quit));
}


void Menu::handleEvents()
{
    while (SDL_PollEvent(&events) != 0) {
        if (events.type == SDL_QUIT) {
            next_state = State_Quit;
        }
        else if (events.type == SDL_MOUSEBUTTONDOWN) {
            check_button_pressed = true;
        }
    }
}

void Menu::update()
{
    if (check_button_pressed) {
        for (const auto& button : buttons) {
            next_state = button->update(next_state);
        }
        check_button_pressed = false;
    }
}

void Menu::draw(SDL_Renderer *renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);

    for (auto& button : buttons) {
        button->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

States Menu::getNextState() const
{
    return next_state;
}
