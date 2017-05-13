#include "ViewHighscore.h"

#include "Constants.h"
#include "Enums.h"
#include "AssetManager.h"
#include "HighscoreFile.h"
#include "Point.h"


ViewHighscore::ViewHighscore(SDL_Renderer* renderer, int last_score)
    : title{renderer, "HIGHSCORE", {SCREEN_WIDTH / 2 - 150, 150}, AssetManager::getInstance().getFont("title")}
{
    back_button.setPosition({SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150});
    back_button.setText("BACK");

    auto scores = HighscoreFile::read();
    createHighscoreText(renderer, scores);
    if (last_score > 0)
    {
	Point score_pos{SCREEN_WIDTH / 2 - 150, 300};
	latest_score.reset(new Text(
			       renderer,
			       "Your score: " + std::to_string(last_score),
			       score_pos,
			       AssetManager::getInstance().getFont("text")));
    }
}

State ViewHighscore::getNextState() const
{
    return next_state;
}

void ViewHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    back_button.draw(renderer);

    for (auto& score : highscores)
    {
	score->draw(renderer);
    }

    if (latest_score)
    {
	latest_score->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void ViewHighscore::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State::QUIT;
        }
	else if (leftMouseButtonPressed())
	{
	    if (back_button.mouseAbove())
	    {
		next_state = State::MENU;
	    }
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
	    if (back_button.mouseAbove())
	    {
		back_button.addHighlight();
		back_button_active = true;
	    }
	    else
	    {
		back_button.removeHighlight();
		back_button_active = false;
	    }
	}
	else if (event.type == SDL_KEYDOWN)
	{
	    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
	    {
		back_button.addHighlight();
		back_button_active = true;
	    }
	    else if (event.key.keysym.sym == SDLK_RETURN)
	    {
		if (back_button_active)
		{
		    next_state = State::MENU;
		}
	    }
	}
    }
}

void ViewHighscore::update() {}

bool ViewHighscore::leftMouseButtonPressed() const
{
    return (event.type == SDL_MOUSEBUTTONDOWN &&
	    SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}

void ViewHighscore::createHighscoreText(SDL_Renderer* renderer,
					const score_t& scores)
{
    int row_y_pos = 400;
    int name_offset = 170;
    int score_offset = 100;

    for (const auto& score : scores)
    {
	highscores.emplace_back(std::make_unique<Text>(
				    renderer, score.first,
				    Point{SCREEN_WIDTH / 2 - name_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	highscores.emplace_back(std::make_unique<Text>(
				    renderer, std::to_string(score.second),
				    Point{SCREEN_WIDTH / 2 + score_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	row_y_pos += 50;
    }
}
