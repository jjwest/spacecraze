#ifndef _VIEW_HIGHSCORE_H_
#define _VIEW_HIGHSCORE_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "GameState.h"
#include "Button.h"
#include "Enums.h"
#include "RenderedText.h"

namespace {
    using score_vec = std::vector<std::pair<std::string, int>>;
}

class ViewHighscore: public GameState
{
public:
    ViewHighscore(SDL_Renderer* renderer, int last_score);
    State getNextState() const override;
    void draw(SDL_Renderer* renderer) override;
    void handleEvents() override;
    void update() override;

private:
    bool back_button_active = false;
    Button back_button;
    SDL_Event event;
    RenderedText title;
    State next_state = State::VIEW_HIGHSCORE;
    std::unique_ptr<RenderedText> latest_score = nullptr;
    std::vector<std::unique_ptr<RenderedText>> highscores;

    bool leftMouseButtonPressed() const;
    void createHighscoreText(SDL_Renderer* renderer, const score_vec& scores);
};


#endif // _VIEW_HIGHSCORE_H_
