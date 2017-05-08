#include "StateManager.h"
#include "Play.h"
#include "Menu.h"
#include "ViewHighscore.h"
#include "EnterHighscore.h"

StateManager::StateManager(SDL_Renderer* r)
    : renderer{r}, current_state(new Menu(r)) {}

bool StateManager::stillPlaying() const
{
    return current_state_id != State::QUIT;
}

State StateManager::getCurrent() const
{
    return current_state_id;
}

void StateManager::update()
{
    current_state->handleEvents();
    current_state->update();
    current_state->draw(renderer);
    auto next_state = current_state->getNextState();
    changeStateIfRequired(next_state);
}

void StateManager::changeStateIfRequired(State next_state)
{
    if (next_state != current_state_id)
    {
        switch (next_state) {
        case State::PLAY:
	{
	    score.reset();
            current_state.reset(new Play(renderer, score));
            break;
	}

        case State::MENU:
	{
	    current_state.reset(new Menu(renderer));
            break;
	}

        case State::VIEW_HIGHSCORE:
	{
	    current_state.reset(new ViewHighscore(renderer, score.get()));
            break;
	}

	case State::ENTER_HIGHSCORE:
	{
	    current_state.reset(new EnterHighscore(renderer, score));
	    break;
	}

	case State::QUIT:
	    break;
	}

    }
    current_state_id = next_state;
}
