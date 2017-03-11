#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "EnemyGenerator.h"
#include "GameState.h"
#include "PowerupGenerator.h"
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
    PowerupGenerator powerup_generator;

    SDL_Event event;
    ScoreKeeper& score;

    State next_state = State::PLAY;
    UserInterface user_interface;
    World world;
};

#endif // _PLAY_H_
