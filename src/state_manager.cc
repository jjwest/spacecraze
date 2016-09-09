#include "state_manager.h"
#include "play.h"
#include "menu.h"
#include "view_highscore.h"
#include "enter_highscore.h"

StateManager::StateManager(SDL_Renderer* r)
    : renderer{r}, current_state(new Menu(r)) {}

bool StateManager::stillPlaying() const
{
    return current_state_id != State_Quit;
}

void StateManager::update()
{
    current_state->handleEvents();
    current_state->update();
    current_state->draw(renderer);
    auto next_state = current_state->getNextState();
    changeStateIfRequired(next_state);
}

void StateManager::changeStateIfRequired(States next_state)
{
    if (next_state != current_state_id)
    {
        switch (next_state) {
        case State_Play:
	    score.reset();
            current_state.reset(new Play(renderer, score));
            break;

        case State_Menu:
            current_state.reset(new Menu(renderer));
            break;

        case State_ViewHighscore:
	    current_state.reset(new ViewHighscore(renderer));
            break;

	case State_EnterHighscore:
	    current_state.reset(new EnterHighscore(renderer, score));
	    break;

	case State_Quit:
	    break;
	}

    }
    current_state_id = next_state;
}
