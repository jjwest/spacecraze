#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <SDL2/SDL.h>

#include "button.h"
#include "gamestate.h"
#include "enums.h"

class Highscore: public GameState
{
public:
    Highscore(SDL_Renderer* renderer);
    GameStates getNextState() const override;
    int getScore() const override;
    void handleEvents() override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
};


#endif // _HIGHSCORE_H_
