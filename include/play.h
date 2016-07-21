#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "game_state.h"
#include "enemy_generator.h"
#include "user_interface.h"
#include "score_keeper.h"
#include "world.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* renderer);
    State getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    EnemyGenerator enemy_generator;
    State next_state = State_Play;
    SDL_Event event;
    UserInterface user_interface;
    ScoreKeeper current_score;
    World world;
};

#endif // _PLAY_H_
