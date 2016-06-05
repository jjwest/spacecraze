#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <SDL2/SDL.h>

#include "enums.h"

class GameState
{
public:
    GameState() {};
    virtual ~GameState() {};
    virtual GameStates getNextState() const = 0;
    virtual int getScore() const { return 0; };
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer*) = 0;
};


#endif // _GAMESTATE_H_
