#include "StateManager.h"

#include "EnterHighscore.h"
#include "Menu.h"
#include "Options.h"
#include "Play.h"
#include "ViewHighscore.h"

StateManager::StateManager(SDL_Renderer* r)
    : renderer{r}, current_state(new Menu()) {}

bool StateManager::stillPlaying() const
{
    return current_state_id != State::QUIT;
}

State StateManager::current() const
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

        case State::MENU:            current_state.reset(new Menu()); break;
		case State::OPTIONS:         current_state.reset(new Options()); break;
        case State::VIEW_HIGHSCORE:  current_state.reset(new ViewHighscore(score.get())); break;
		case State::ENTER_HIGHSCORE: current_state.reset(new EnterHighscore(score)); break;
		case State::QUIT: break;
		}

    }
    current_state_id = next_state;
}
