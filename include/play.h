#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>

#include "gamestate.h"
#include "enemy_generator.h"
#include "game_world.h"

class Play: public GameState
{
public:
    Play();
    GameStates getNextState() const;
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Event event;
    GameStates next_state;
    EnemyGenerator enemy_generator;
    std::unique_ptr<GameWorld> world;
};

#endif // _PLAY_H_
