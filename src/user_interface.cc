#include "user_interface.h"
#include "assets.h"
#include "point.h"

UserInterface::UserInterface(SDL_Renderer* renderer)
    : singularity{ Assets::getInstance().getTexture("singularity"),
        Point{ 950, 50 } }
{
    updateScoreTexture(renderer, 0);
}

void UserInterface::draw(SDL_Renderer* renderer, int new_score,
                         bool player_has_special)
{
    if (score != new_score)
    {
        updateScoreTexture(renderer, new_score);
        score = new_score;
    }
    if (player_has_special)
    {
        singularity.draw(renderer);
    }
    rendered_score->draw(renderer);
}

void UserInterface::updateScoreTexture(SDL_Renderer* renderer, int new_score)
{
    TTF_Font* font = Assets::getInstance().getFont("text");
    rendered_score.reset(new RenderedText(
			     renderer,
			     std::to_string(new_score),
			     {950, 30},
			     font));

}
