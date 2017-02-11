#include "ViewHighscore.h"

#include "Constants.h"
#include "Enums.h"
#include "AssetManager.h"
#include "HighscoreFile.h"
#include "Point.h"

const Point button_pos{constants::SCREEN_WIDTH / 2 - 50, constants::SCREEN_HEIGHT - 150};
const Point title_pos{constants::SCREEN_WIDTH / 2 - 150, 150};

ViewHighscore::ViewHighscore(SDL_Renderer* renderer, int last_score)
    : button_back{renderer, button_pos, "BACK", State_Menu},
      title{renderer, "HIGHSCORE", title_pos, AssetManager::getInstance().getFont("title")}
{
    auto scores = HighscoreFile::read();
    createHighscoreText(renderer, scores);

    if (last_score > 0)
    {
	Point score_pos{constants::SCREEN_WIDTH / 2 - 150, 300};
	latest_score.reset(new RenderedText(
			       renderer,
			       "Your score: " + std::to_string(last_score),
			       score_pos,
			       AssetManager::getInstance().getFont("text")));
    }
}

States ViewHighscore::getNextState() const
{
    return next_state;
}

void ViewHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    button_back.draw(renderer);

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
            next_state = State_Quit;
        }
	else if (leftMouseButtonPressed())
	{
	    next_state = button_back.update(next_state);
	}
    }
}

void ViewHighscore::update() {}

bool ViewHighscore::leftMouseButtonPressed() const
{
    return event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT);
}

void ViewHighscore::createHighscoreText(SDL_Renderer* renderer,
					const score_vec& scores)
{
    int row_y_pos = 400;
    int name_offset = 170;
    int score_offset = 100;

    for (const auto& score : scores)
    {
	highscores.emplace_back(std::make_unique<RenderedText>(
				    renderer, score.first,
				    Point{constants::SCREEN_WIDTH / 2 - name_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	highscores.emplace_back(std::make_unique<RenderedText>(
				    renderer, std::to_string(score.second),
				    Point{constants::SCREEN_WIDTH / 2 + score_offset, row_y_pos},
				    AssetManager::getInstance().getFont("text")));
	row_y_pos += 50;
    }
}
