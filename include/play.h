#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "game_state.h"
#include "enemy_generator.h"
#include "user_interface.h"
#include "world.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* renderer);
    States getNextState() const override;
    int getScore() const;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    EnemyGenerator enemy_generator;
    States next_state = State_Play;
    SDL_Event event;
    UserInterface user_interface;
    int current_score;
    World world;
};

#endif // _PLAY_H_
