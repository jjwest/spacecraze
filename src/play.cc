#include "../include/play.h"

Play::Play(SDL_Renderer* r)
    : GameState(), renderer{r}, next_state{PLAY} {}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT) 
        {
            next_state = QUIT;
        }
    }
}

void Play::update()
{
    handleEvents();
    enemy_generator.update(world);
}

void Play::render()
{
    
}

GameStates Play::getNextState()
{
    return next_state;
}

