#include "play.h"

#include "assets.h"
#include "texture.h"

#include <iostream>

Play::Play(SDL_Renderer* renderer, ScoreKeeper& s)
    : GameState(),
      user_interface{renderer},
      score{s} {}


States Play::getNextState() const
{
    return next_state;
}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
	{
            next_state = State_Quit;
        }
    }
}

void Play::update()
{
    enemy_generator.update(world);
    score.increaseScore(world.update());

    if (world.playerIsDead())
    {
        next_state = State_EnterHighscore;
    }
}

void Play::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    auto background = Assets::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    world.draw(renderer);
    user_interface.draw(renderer, score.getScore());
    SDL_RenderPresent(renderer);
}
