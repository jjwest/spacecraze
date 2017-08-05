#include "EnterHighscore.h"

#include <algorithm>

#include "AssetManager.h"
#include "Constants.h"
#include "HighscoreFile.h"

EnterHighscore::EnterHighscore(const ScoreKeeper& score)
    : player_score{score.get()}
{
    back_button.setPosition(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150);
    back_button.setText("BACK");

    SDL_StartTextInput();

    if (!goodEnoughForHighscore(player_score))
    {
	next_state = State::VIEW_HIGHSCORE;
    }
}

EnterHighscore::~EnterHighscore()
{
    SDL_StopTextInput();
}

State EnterHighscore::getNextState() const
{
    return next_state;
}

void EnterHighscore::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
	    next_state = State::QUIT;
        }
	else if (leftMouseButtonPressed())
	{
	    if (back_button.mouseOver())
	    {
		next_state = State::MENU;
	    }
	}
	else if (backspaceIsPressed() && !player_name.empty())
	{
	    player_name.pop_back();
	    name_changed = true;
	}
	else if (returnIsPressed())
	{
	    updateHighscoreFile();
	    next_state = State::VIEW_HIGHSCORE;
	}
	else if (enteringName())
	{
	    std::string input = event.text.text;
	    if (!containsSpace(input))
	    {
		if (player_name.size() < 6)
		{
		    player_name += input;
		    name_changed = true;
		}
	    }
	}
    }
}

void EnterHighscore::update() {}

void EnterHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::instance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    back_button.draw(renderer);

    if (name_changed)
    {
	if (!player_name.empty())
	{
	    rendered_player_name.reset(new Text());
	    rendered_player_name->setText(player_name);
	    rendered_player_name->setPosition(550, 700);
	    rendered_player_name->setFont(AssetManager::instance().getFont("text"));
	}
	else
	{
	    rendered_player_name.release();
	}

	name_changed = false;
    }

    if (rendered_player_name)
    {
	rendered_player_name->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

bool EnterHighscore::goodEnoughForHighscore(int score) const
{
    auto highscores = HighscoreFile::read();
    return score > 0 && (highscores.size() < 5 || score > highscores.back().score);
}


bool EnterHighscore::leftMouseButtonPressed() const
{
    return (event.type == SDL_MOUSEBUTTONDOWN &&
	    SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}

bool EnterHighscore::backspaceIsPressed() const
{
    return event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE;
}

bool EnterHighscore::returnIsPressed() const
{
    return event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN;
}

void EnterHighscore::updateHighscoreFile() const
{
    auto highscores = HighscoreFile::read();

    if (highscores.size() == 5)
    {
	highscores.pop_back();
    }

    highscores.push_back( {player_name, player_score} );
    std::sort(begin(highscores), end(highscores),
	      [] (const auto& a, const auto& b)
	      {
		  return a.score > b.score;
	      });

    HighscoreFile::write(highscores);
}

bool EnterHighscore::enteringName() const
{
    return event.type == SDL_TEXTINPUT;
}

bool EnterHighscore::containsSpace(const std::string& input) const
{
    return input.find(' ') != std::string::npos;
}
