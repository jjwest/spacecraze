#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include <map>

#include "../inc/world.h"
#include "enemy_generator.h"
#include "enums.h"

class PlayState {
public:
    PlayState();
    ~PlayState();
    GameStates update(SDL_Renderer*, SDL_Event&);
    
private:
    World world;
    EnemyGenerator enemy_generator;
    InputHandler input_handler;    
};


#endif // _PLAYSTATE_H_
