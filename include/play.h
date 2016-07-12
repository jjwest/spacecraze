#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "game_state.h"
#include "enemy_generator.h"
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
    State next_state = PLAY;
    SDL_Event event;
    World world;
};

#endif // _PLAY_H_
