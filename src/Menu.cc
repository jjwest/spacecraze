#include "Menu.h"
#include "AssetManager.h"
#include "Point.h"
#include <iostream>

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
	    if (play_button.mouseAbove())
	    {
		next_state = State::PLAY;
	    }
	    else if (highscore_button.mouseAbove())
	    {
		next_state = State::VIEW_HIGHSCORE;
	    }
	    else if (quit_button.mouseAbove())
	    {
		next_state = State::QUIT;
	    }
        }
	else if (event.type == SDL_KEYDOWN)
	{
	    if (active_button == NONE)
	    {
		active_button = PLAY;
	    }
	    else if (event.key.keysym.sym == SDLK_UP && active_button != PLAY)
	    {
		--active_button;
	    }
	    else if (event.key.keysym.sym == SDLK_DOWN && active_button != BUTTON_COUNT - 1)
	    {
		++active_button;
	    }
	    else if (event.key.keysym.sym == SDLK_RETURN)
	    {
		switch (active_button)
		{
		case PLAY:      next_state = State::PLAY; break;
		case HIGHSCORE: next_state = State::VIEW_HIGHSCORE; break;
		case QUIT:      next_state = State::QUIT; break;
		}
	    }
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
	    if (play_button.mouseAbove())
	    {
		active_button = PLAY;
	    }
	    else if (highscore_button.mouseAbove())
	    {
		active_button = HIGHSCORE;
	    }
	    else if (quit_button.mouseAbove())
	    {
		active_button = QUIT;
	    }
	}
    }
}

void Menu::update() {
    switch (active_button)
    {
    case PLAY:
    {
	play_button.addHighlight();
	highscore_button.removeHighlight();
	quit_button.removeHighlight();
	break;
    }
    case HIGHSCORE:
    {
	highscore_button.addHighlight();
	play_button.removeHighlight();
	quit_button.removeHighlight();
	break;
    }
    case QUIT:
    {
	quit_button.addHighlight();
	highscore_button.removeHighlight();
	play_button.removeHighlight();
	break;
    }
    }
}

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
