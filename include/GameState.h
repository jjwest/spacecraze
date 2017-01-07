#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <SDL2/SDL.h>

#include "Enums.h"

class GameState
{
public:
    GameState() {};
    virtual ~GameState() {};
    virtual States getNextState() const = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
};


#endif // _GAMESTATE_H_
