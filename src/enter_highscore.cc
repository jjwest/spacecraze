#include "enter_highscore.h"
#include "asset_manager.h"
#include "constants.h"

EnterHighscore::EnterHighscore(SDL_Renderer* renderer)
    : button_back{renderer,
    {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150},
	"BACK", State_Menu} {}

States EnterHighscore::getNextState() const
{
    return next_state;
}

void EnterHighscore::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State_Quit;
        }
	else if (event.type == SDL_MOUSEBUTTONDOWN &&
		   SDL_BUTTON(SDL_BUTTON_LEFT))
	{
	    update_buttons = true;
	}
    }
}

void EnterHighscore::update()
{
    if (update_buttons)
    {
	next_state = button_back.update(next_state);
	update_buttons = false;
    }
}

void EnterHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    button_back.draw(renderer);

    SDL_RenderPresent(renderer);
}
