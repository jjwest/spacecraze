#ifndef _ENTER_HIGHSCORE_H_
#define _ENTER_HIGHSCORE_H_

#include <SDL2/SDL.h>
#include <vector>

#include "game_state.h"
#include "enums.h"

class EnterHighscore: public GameState
{
public:
    EnterHighscore(SDL_Renderer* renderer);
    States getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:

};


#endif // _ENTER_HIGHSCORE_H_
