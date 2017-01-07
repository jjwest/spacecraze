#include "UserInterface.h"
#include "AssetManager.h"
#include "Point.h"

UserInterface::UserInterface()
    : special_weapon(AssetManager::getInstance().getTexture("singularity"),
		     SDL_Rect{1070, 20, 50, 50}) {}

void UserInterface::draw(SDL_Renderer* renderer)
{
    if (player_has_special)
    {
	special_weapon.draw(renderer);
    }
    if (score_changed)
    {
        updateScoreTexture(renderer);
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

void UserInterface::updateScoreTexture(SDL_Renderer* renderer)
{
    auto font = AssetManager::getInstance().getFont("text");
    rendered_score.reset(new RenderedText(
			     renderer,
			     std::to_string(score),
			     Point{950, 30},
			     font));

}
