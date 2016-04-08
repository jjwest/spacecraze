#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <SDL2/SDL.h>
#include <vector>

#include "gamestate.h"
#include "rendered_text.h"
#include "button.h"
#include "enums.h"

class Highscore: public GameState
{
public:
    Highscore(SDL_Renderer* renderer);
    GameStates getNextState() const;
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Event events;
    GameStates next_state = HIGHSCORE;
    Button button_back;
    RenderedText title;
    std::vector<RenderedText> highscore_entries;

    void checkButtonPressed();
};

#endif // _HIGHSCORE_H_
