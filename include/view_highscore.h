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
    State getNextState() const;
    void handleEvents();
    void update();
    void draw(SDL_Renderer* renderer);

private:
    SDL_Event events;
    Button back;
    RenderedText title;
    std::vector<RenderedText> scores;
};


#endif // _VIEW_HIGHSCORE_H_
