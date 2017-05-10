#include "Menu.h"
#include "AssetManager.h"
#include "Point.h"

Menu::Menu(SDL_Renderer* renderer)
    : title{ renderer,
              "SPACECRAZE",
              {450, 150},
              AssetManager::getInstance().getFont("title")}
{
    play_button.setPosition({550, 400});
    play_button.setText(renderer, "PLAY");
    highscore_button.setPosition({550, 450});
    highscore_button.setText(renderer, "HIGHSCORE");
    quit_button.setPosition({550, 500});
    quit_button.setText(renderer, "QUIT");
}


void Menu::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State::QUIT;
        }
        else if (leftMouseButtonPressed())
	{
	    if (play_button.pressed())
	    {
		next_state = State::PLAY;
	    }
	    else if (highscore_button.pressed())
	    {
		next_state = State::VIEW_HIGHSCORE;
	    }
	    else if (quit_button.pressed())
	    {
		next_state = State::QUIT;
	    }
        }
    }
}

void Menu::update() {}

void Menu::draw(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    title.draw(renderer);
    play_button.draw(renderer);
    highscore_button.draw(renderer);
    quit_button.draw(renderer);

    SDL_RenderPresent(renderer);
}

State Menu::getNextState() const
{
    return next_state;
}

bool Menu::leftMouseButtonPressed() const
{
    return (event.type == SDL_MOUSEBUTTONDOWN &&
	    SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}
