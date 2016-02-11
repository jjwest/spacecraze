#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>
#include <memory>

#include "gamestate.h"
#include "player.h"
#include "laser_manager.h"
#include "enemy_generator.h"
#include "enemy_manager.h"
#include "enums.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* r);
    ~Play();
    void handleEvents();
    void update();
    void render();
    GameStates nextState();

private:
    SDL_Event event;
    SDL_Renderer* renderer;

    EnemyManager enemy_manager;
    LaserManager laser_manager;
    Player player;

    GameStates next_state;
};


#endif // _PLAY_H_
