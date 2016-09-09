#include "play.h"

#include "assets.h"
#include "texture.h"
#include "world.h"

#include <iostream>

Play::Play(SDL_Renderer* renderer, ScoreKeeper& s)
    : GameState(), user_interface{renderer}, score{s} {}


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
    int score_increment = world.update();
    score.increaseScore(score_increment);

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
    SDL_RenderPresent(renderer);
}
