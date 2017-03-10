#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "GameState.h"
#include "EnemyGenerator.h"
#include "UserInterface.h"
#include "World.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* renderer, ScoreKeeper& score);
    State getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    EnemyGenerator enemy_generator;
    State next_state = State::PLAY;
    SDL_Event event;
    UserInterface user_interface;
    ScoreKeeper& score;
    World world;
};

#endif // _PLAY_H_
