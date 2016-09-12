#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <SDL2/SDL.h>
#include <memory>

#include "enums.h"
#include "game_state.h"
#include "score_keeper.h"

class StateManager
{
public:
    StateManager(SDL_Renderer* r);
    bool stillPlaying() const;
    States getCurrent() const;
    void update();

private:
    SDL_Renderer* renderer;
    ScoreKeeper score;
    std::unique_ptr<GameState> current_state;
    States current_state_id = State_Menu;

    void changeStateIfRequired(States next_state);
};


#endif // _STATE_MANAGER_H_
