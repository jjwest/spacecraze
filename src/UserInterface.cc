#include "UserInterface.h"
#include "AssetManager.h"
#include "Point.h"

UserInterface::UserInterface()
    : special_weapon(AssetManager::instance().getTexture("singularity"),
					 SDL_Rect{1070, 20, 50, 50}) {}

void UserInterface::draw(SDL_Renderer* renderer)
{
    if (player_has_special)
    {
		special_weapon.draw(renderer);
    }
    if (score_changed)
    {
		auto font = AssetManager::instance().getFont("text");
		rendered_score.reset(new Text());
		rendered_score->setText(std::to_string(score));
		rendered_score->setPosition(950, 30);
		rendered_score->setFont(font);
    }

    rendered_score->draw(renderer);
}

void UserInterface::update(int new_score, bool has_special)
{
    player_has_special = has_special;
    if (score != new_score)
    {
		score = new_score;
		score_changed = true;
    }
}
