#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>
#include <memory>
#include <map>

#include "gamestate.h"
#include "player.h"
#include "laser_manager.h"
#include "enemy_generator.h"
#include "world.h"

class Play: public GameState
{
public:
    Play();
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);
    GameStates getNextState() const;

private:
    SDL_Event event;
    GameStates next_state;
    EnemyGenerator enemy_generator;
    World world;
};

#endif // _PLAY_H_
