#include "view_highscore.h"
#include "constants.h"
#include "enums.h"
#include "asset_manager.h"
#include "file_manager.h"
#include "point.h"

ViewHighscore::ViewHighscore(SDL_Renderer* renderer)
    : button_back{renderer,
        {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150},
	"BACK", State_Menu},
    title{renderer,
	    "HIGHSCORE",
	    {SCREEN_WIDTH / 2 - 150, 150},
	    AssetManager::getInstance().getFont("title")}
{
    auto scores = FileManager::readHighscore("highscore.txt");
    createHighscoreText(renderer, scores);
}

States ViewHighscore::getNextState() const
{
    return next_state;
}

void ViewHighscore::handleEvents()
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

void ViewHighscore::update()
{
    if (update_buttons)
    {
	next_state = button_back.update(next_state);
    }
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

    SDL_RenderPresent(renderer);
}

void ViewHighscore::createHighscoreText(SDL_Renderer* renderer,
					const std::vector<std::string>& scores)
{
    int score_y_pos = 400;
    for (const auto& score : scores)
    {
	highscores.emplace_back(std::make_unique<RenderedText>(
				    renderer, score,
				    Point{SCREEN_WIDTH / 2 - 170, score_y_pos},
				    AssetManager::getInstance().getFont("text")));
	score_y_pos += 50;
    }
}
