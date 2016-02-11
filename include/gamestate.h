#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "enums.h"

class GameState
{
public:
    GameState();
    virtual ~GameState();
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual GameStates nextState() = 0;

private:
    virtual void setNextState(GameStates state) = 0;
};


#endif // _GAMESTATE_H_