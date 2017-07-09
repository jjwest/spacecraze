#include "Play.h"

#include "AssetManager.h"
#include "Texture.h"

Play::Play(SDL_Renderer*, ScoreKeeper& score)
    : GameState(),
      score{score} {}


State Play::getNextState() const
{
    return next_state;
}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State::QUIT;
        }
    }
}

void Play::update()
{
    enemy_generator.update(world);
    powerup_generator.update(world);
    world.update();
    auto state = world.getState();
    user_interface.update(state.score, state.player_has_special);

    if (state.player_dead)
    {
        next_state = State::ENTER_HIGHSCORE;
	score.set(state.score);
    }
}

void Play::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    world.draw(renderer);
    user_interface.draw(renderer);

    SDL_RenderPresent(renderer);
}
