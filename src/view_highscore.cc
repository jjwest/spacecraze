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
    FileManager f;
    auto scores = f.readHighscoreFromFile(HIGHSCORE_FILE_PATH);
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
	    left_mouse_key_pressed = true;
	}
    }
}

void ViewHighscore::update()
{
    if (left_mouse_key_pressed)
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
					const scores& scores)
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
