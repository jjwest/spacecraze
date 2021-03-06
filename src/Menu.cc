#include "Menu.h"
#include "AssetManager.h"
#include "Point.h"

Menu::Menu()
{
    title.setText("SPACECRAZE");
    title.setPosition(450, 150);
    title.setFont(AssetManager::instance().getFont("title"));

    play_button.setText("PLAY");
    play_button.setPosition(550, 400);

    highscore_button.setText("HIGHSCORE");
    highscore_button.setPosition(550, 450);

    options_button.setText("OPTIONS");
    options_button.setPosition(550, 500);

    quit_button.setText("QUIT");
    quit_button.setPosition(550, 550);
}


void Menu::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) next_state = State::QUIT;

        else if (leftMouseButtonPressed())
		{
			if (play_button.mouseOver()) next_state = State::PLAY;
			else if (highscore_button.mouseOver()) next_state = State::VIEW_HIGHSCORE;
			else if (options_button.mouseOver()) next_state = State::OPTIONS;
			else if (quit_button.mouseOver()) next_state = State::QUIT;
        }
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP && active_button > PLAY) --active_button;
			else if (event.key.keysym.sym == SDLK_DOWN && active_button != QUIT) ++active_button;
			else if (event.key.keysym.sym == SDLK_RETURN)
			{
				switch (active_button)
				{
				case PLAY:      next_state = State::PLAY; break;
				case HIGHSCORE: next_state = State::VIEW_HIGHSCORE; break;
				case OPTIONS:   next_state = State::OPTIONS; break;
				case QUIT:      next_state = State::QUIT; break;
				}
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			active_button = NONE;

			if (play_button.mouseOver()) active_button = PLAY;
			else if (highscore_button.mouseOver()) active_button = HIGHSCORE;
			else if (options_button.mouseOver()) active_button = OPTIONS;
			else if (quit_button.mouseOver()) active_button = QUIT;
		}
    }
}

void Menu::update()
{
    switch (active_button)
    {
    case PLAY:
    {
		play_button.addHighlight();
		highscore_button.removeHighlight();
		quit_button.removeHighlight();
		options_button.removeHighlight();
		break;
    }
    case HIGHSCORE:
    {
		highscore_button.addHighlight();
		play_button.removeHighlight();
		quit_button.removeHighlight();
		options_button.removeHighlight();
		break;
    }
    case OPTIONS:
    {
		options_button.addHighlight();
		highscore_button.removeHighlight();
		play_button.removeHighlight();
		quit_button.removeHighlight();
		break;
    }
    case QUIT:
    {
		quit_button.addHighlight();
		highscore_button.removeHighlight();
		play_button.removeHighlight();
		options_button.removeHighlight();
		break;
    }
    case NONE:
    {
		quit_button.removeHighlight();
		highscore_button.removeHighlight();
		play_button.removeHighlight();
		options_button.removeHighlight();
		break;
    }
    }
}

void Menu::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::instance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    title.draw(renderer);
    play_button.draw(renderer);
    highscore_button.draw(renderer);
    options_button.draw(renderer);
    quit_button.draw(renderer);

    SDL_RenderPresent(renderer);
}

State Menu::getNextState() const
{
    return next_state;
}

bool Menu::leftMouseButtonPressed() const
{
    return (event.type == SDL_MOUSEBUTTONDOWN
			&& SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}
