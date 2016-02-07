#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include <SDL2/SDL.h>

#include "input_handler.h"
#include "../inc/enums.h"

class PlayState
{
public:
    PlayState();
    GameStates update();

private:
    InputHandler input;
    
};


#endif // _PLAY_STATE_H_



// MANAGE INPUT
// GENERATE ENEMIES
// UPDATE OBJECTS
// CHECK COLLISIONS
// RENDER
