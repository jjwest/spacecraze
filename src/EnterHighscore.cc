#include "EnterHighscore.h"

#include <algorithm>
#include <iostream>

#include "AssetManager.h"
#include "Constants.h"
#include "HighscoreFile.h"

const Point button_position = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150};

EnterHighscore::EnterHighscore(SDL_Renderer* renderer, const ScoreKeeper& score)
    : back_button {renderer, button_position, "BACK", State_Menu},
      player_score{score.get()}
{
    SDL_StartTextInput();

    if (!goodEnoughForHighscore(player_score))
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
	    next_state = back_button.update(next_state);
	}
	else if (backspaceIsPressed() && !player_name.empty())
	{
	    player_name.pop_back();
	}
	else if (returnIsPressed())
	{
	    updateHighscoreFile();
	    next_state = State_ViewHighscore;
	}
	else if (enteringName())
	{
	    std::string input = event.text.text;
	    if (!containsSpace(input))
	    {
		player_name += input;
	    }
	}
    }
}

void EnterHighscore::update() {}

void EnterHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    back_button.draw(renderer);
    renderUserInput(renderer);
    if (rendered_player_name)
    {
	rendered_player_name->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void EnterHighscore::renderUserInput(SDL_Renderer* renderer)
{
    if (!player_name.empty())
    {
	rendered_player_name.reset(
	    new RenderedText(
		renderer,
		player_name,
		Point{550, 700},
		AssetManager::getInstance().getFont("text"))
	    );
    }
    else
    {
	rendered_player_name.release();
    }
}

bool EnterHighscore::goodEnoughForHighscore(int score) const
{
    auto highscores = HighscoreFile::read();
    return score > 0 && (highscores.size() < 5 || score > highscores.back().second);
}


bool EnterHighscore::leftMouseButtonPressed() const
{
    return event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT);
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
		  return a.second > b.second;
	      });

    for (const auto& score : highscores)
    {
	std::cout << score.second << '\n';
    }
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
