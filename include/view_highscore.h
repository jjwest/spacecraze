#ifndef _VIEW_HIGHSCORE_H_
#define _VIEW_HIGHSCORE_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "game_state.h"
#include "button.h"
#include "enums.h"
#include "rendered_text.h"

namespace {
    using score_vec = std::vector<std::pair<std::string, int>>;
}

class ViewHighscore: public GameState
{
public:
    ViewHighscore(SDL_Renderer* renderer);
    States getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    bool left_mouse_key_pressed = false;
    Button button_back;
    SDL_Event event;
    RenderedText title;
    States next_state = State_ViewHighscore;
    std::vector<std::unique_ptr<RenderedText>> highscores;

    void createHighscoreText(SDL_Renderer* renderer, const score_vec& scores);
};


#endif // _VIEW_HIGHSCORE_H_
