#include "ViewHighscore.h"

#include "Constants.h"
#include "Enums.h"
#include "AssetManager.h"
#include "HighscoreFile.h"
#include "Point.h"

const Point button_pos{SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150};
const Point title_pos{SCREEN_WIDTH / 2 - 150, 150};

ViewHighscore::ViewHighscore(SDL_Renderer* renderer, int last_score)
    : title{renderer, "HIGHSCORE", title_pos, AssetManager::getInstance().getFont("title")}
{
    back_button.setPosition(button_pos);
    back_button.setText(renderer, "BACK");

    auto scores = HighscoreFile::read();
    createHighscoreText(renderer, scores);
    if (last_score > 0)
    {
	Point score_pos{SCREEN_WIDTH / 2 - 150, 300};
	latest_score.reset(new RenderedText(
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
	highscores.emplace_back(std::make_unique<RenderedText>(
				    renderer, score.first,
				    Point{SCREEN_WIDTH / 2 - name_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	highscores.emplace_back(std::make_unique<RenderedText>(
				    renderer, std::to_string(score.second),
				    Point{SCREEN_WIDTH / 2 + score_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	row_y_pos += 50;
    }
}
