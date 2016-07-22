#ifndef _VIEW_HIGHSCORE_H_
#define _VIEW_HIGHSCORE_H_

#include <SDL2/SDL.h>

#include <vector>

#include "game_state.h"
#include "button.h"
#include "enums.h"
#include "rendered_text.h"

class ViewHighscore: public GameState
{
public:
    ViewHighscore(SDL_Renderer* renderer);
    States getNextState() const;
    void handleEvents();
    void update();
    void draw(SDL_Renderer* renderer);

private:
    SDL_Event event;
    Button button_back;
    RenderedText title;
    std::vector<RenderedText> scores;
    States next_state = State_ViewHighscore;
};


#endif // _VIEW_HIGHSCORE_H_
