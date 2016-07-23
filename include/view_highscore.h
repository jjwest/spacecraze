#ifndef _VIEW_HIGHSCORE_H_
#define _VIEW_HIGHSCORE_H_

#include <SDL2/SDL.h>

#include <memory>
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
    bool update_buttons = false;
    Button button_back;
    SDL_Event event;
    RenderedText title;
    States next_state = State_ViewHighscore;
    std::vector<std::unique_ptr<RenderedText>> highscores;

    void createHighscoreText(SDL_Renderer* renderer,
			     const std::vector<std::string>& scores);
};


#endif // _VIEW_HIGHSCORE_H_
