#include "enter_highscore.h"

#include "asset_manager.h"
#include "constants.h"
#include "file_manager.h"

EnterHighscore::EnterHighscore(SDL_Renderer* renderer, int score)
    : button_back{renderer,
    {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150}, "BACK", State_Menu},
      rendered_user_input{}
{
    if ( goodEnoughForHighscore(score) )
    {
	SDL_StartTextInput();
    }
    else
    {
	next_state = State_ViewHighscore;
    }
}

EnterHighscore::~EnterHighscore()
{
    SDL_StopTextInput();
}

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
	else if (leftMouseButtonPressed())
	{
	    update_buttons = true;
	}
	else if (keyIsPressed())
	{
	    if (backspaceIsPressed())
	    {
		user_input_text.pop_back();
		user_input_updated = true;
	    }
	    else if (returnIsPressed())
	    {
		SDL_StopTextInput();
	    }
	}
	else if (playerIsEnteringName())
	{
	    user_input_text += event.text.text;
	    user_input_updated = true;
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

    if (user_input_updated)
    {
	renderNewUserInput(renderer);
    }
    if (rendered_user_input)
    {
	rendered_user_input->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void EnterHighscore::renderNewUserInput(SDL_Renderer* renderer)
{
    if (user_input_text.length() != 0)
    {
	rendered_user_input.reset(
	    new RenderedText(
		renderer,
		user_input_text,
		{550, 700},
		AssetManager::getInstance().getFont("text"))
	    );
    }
    else
    {
	rendered_user_input.release();
    }

    user_input_updated = false;
}

bool EnterHighscore::goodEnoughForHighscore(int score) const
{
    FileManager f;
    auto highscores = f.readHighscoreFromFile(HIGHSCORE_FILE_PATH);

    return highscores.size() < 5 || score > highscores.back().second;
}


bool EnterHighscore::leftMouseButtonPressed() const
{
    return event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool EnterHighscore::keyIsPressed() const
{
    return event.type == SDL_KEYDOWN;
}

bool EnterHighscore::backspaceIsPressed() const
{
    return event.key.keysym.sym == SDLK_BACKSPACE
	&& user_input_text.length() > 0;
}

bool EnterHighscore::returnIsPressed() const
{
    return event.key.keysym.sym == SDLK_RETURN;
}

bool EnterHighscore::playerIsEnteringName() const
{
    return event.type == SDL_TEXTINPUT;;
}
