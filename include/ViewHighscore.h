#ifndef _VIEW_HIGHSCORE_H_
#define _VIEW_HIGHSCORE_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "Button.h"
#include "Enums.h"
#include "GameState.h"
#include "Text.h"

class ViewHighscore: public GameState
{
public:
    ViewHighscore(int last_score);
    State getNextState() const override;
    void draw(SDL_Renderer* renderer) override;
    void handleEvents() override;
    void update() override;

private:
    SDL_Event event;

    Button back_button;
    bool back_button_active = false;
    bool render_new_textures = true;
    Text title;
    State next_state = State::VIEW_HIGHSCORE;
    std::unique_ptr<Text> latest_score = nullptr;
    std::vector<std::unique_ptr<Text>> highscores;

    bool leftMouseButtonPressed() const;
};


#endif // _VIEW_HIGHSCORE_H_
