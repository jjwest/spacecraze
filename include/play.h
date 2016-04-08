#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "gamestate.h"
#include "enemy_generator.h"
#include "world.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* renderer);
    GameStates getNextState() const;
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);

private:
    EnemyGenerator enemy_generator;
    GameStates next_state;
    SDL_Event event;
    World world;
};

#endif // _PLAY_H_
