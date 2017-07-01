#include "ViewHighscore.h"

#include "AssetManager.h"
#include "Constants.h"
#include "Enums.h"
#include "HighscoreFile.h"
#include "Point.h"


ViewHighscore::ViewHighscore(int last_score)
{
    title.setText("HIGHSCORE");
    title.setPosition(SCREEN_WIDTH / 2 - 150, 150);
    title.setFont(AssetManager::getInstance().getFont("title"));
    back_button.setPosition(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150);
    back_button.setText("BACK");

    if (last_score > 0)
    {
	latest_score.reset(new Text());
	latest_score->setText("Your score: " + std::to_string(last_score));
	latest_score->setPosition(SCREEN_WIDTH / 2 - 150, 300);
	latest_score->setFont(AssetManager::getInstance().getFont("text"));
    }
}

State ViewHighscore::getNextState() const
{
    return next_state;
}

void ViewHighscore::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    if (render_new_textures)
    {
	auto score_entries = HighscoreFile::read();
	auto font = AssetManager::getInstance().getFont("text");
	int row_y_pos = 400;
	int name_x_pos = SCREEN_WIDTH / 2 - 170;
	int score_x_pos = SCREEN_WIDTH / 2 + 100;

	for (const auto& entry : score_entries)
	{
	    auto name = std::make_unique<Text>();
	    name->setText(entry.first);
	    name->setPosition(name_x_pos, row_y_pos);
	    name->setFont(font);
	    highscores.push_back(std::move(name));

	    auto score = std::make_unique<Text>();
	    score->setText(std::to_string(entry.second));
	    score->setPosition(score_x_pos, row_y_pos);
	    score->setFont(font);
	    highscores.push_back(std::move(score));

	    row_y_pos += 50;
	}
    }

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    back_button.draw(renderer);

    for (auto& entry : highscores)
    {
	entry->draw(renderer);
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
	    if (back_button.mouseOver())
	    {
		next_state = State::MENU;
	    }
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
	    if (back_button.mouseOver())
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
