#include "user_interface.h"
#include "assets.h"
#include "point.h"

UserInterface::UserInterface(SDL_Renderer* renderer)
{
    updateScoreTexture(renderer, 0);
}

void UserInterface::draw(SDL_Renderer* renderer, int new_score)
{
    if (score != new_score)
    {
        updateScoreTexture(renderer, new_score);
        score = new_score;
    }
    rendered_score->draw(renderer);
}

void UserInterface::updateScoreTexture(SDL_Renderer* renderer, int new_score)
{
    auto font = Assets::getInstance().getFont("text");
    rendered_score.reset(new RenderedText(
			     renderer,
			     std::to_string(new_score),
			     Point{950, 30},
			     font));

}
