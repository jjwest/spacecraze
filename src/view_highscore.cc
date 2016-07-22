#include "view_highscore.h"
#include "constants.h"
#include "enums.h"
#include "asset_manager.h"

ViewHighscore::ViewHighscore(SDL_Renderer* renderer)
    : button_back{ renderer, {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 150},
	"BACK", State_Menu},
      title{renderer, "HIGHSCORE", {SCREEN_WIDTH / 2 - 150, 150},
	      AssetManager::getInstance().getFont("title")}
{

}

States ViewHighscore::getNextState() const
{
    return next_state;
}

void ViewHighscore::handleEvents()
{
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            next_state = State_Quit;
        }
    }
}

void ViewHighscore::update()
{
    next_state = button_back.update(next_state);
}

void ViewHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    button_back.draw(renderer);

    for (auto& score : scores)
    {
	score.draw(renderer);
    }

    SDL_RenderPresent(renderer);
}
