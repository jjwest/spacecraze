#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <SDL2/SDL.h>
#include <memory>

#include "Enums.h"
#include "GameState.h"
#include "ScoreKeeper.h"

class StateManager
{
public:
    StateManager(SDL_Renderer* r);
    bool stillPlaying() const;
    State getCurrent() const;
    void update();

private:
    SDL_Renderer* renderer;
    ScoreKeeper score;
    std::unique_ptr<GameState> current_state;
    State current_state_id = State::MENU;

    void changeStateIfRequired(State next_state);
};


#endif // _STATE_MANAGER_H_
