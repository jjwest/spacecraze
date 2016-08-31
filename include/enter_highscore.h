#ifndef _ENTER_HIGHSCORE_H_
#define _ENTER_HIGHSCORE_H_

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

#include "button.h"
#include "game_state.h"
#include "enums.h"
#include "rendered_text.h"

class EnterHighscore: public GameState
{
public:
    EnterHighscore(SDL_Renderer* renderer, int score);
    ~EnterHighscore();
    States getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:
    bool update_buttons = false;
    bool user_input_updated = false;
    Button button_back;
    SDL_Event event;
    States next_state = State_EnterHighscore;
    std::string user_input_text;
    std::unique_ptr<RenderedText> rendered_user_input;

    void renderNewUserInput(SDL_Renderer* renderer);
    bool goodEnoughForHighscore(int score) const;
    bool leftMouseButtonPressed() const;
    bool keyIsPressed() const;
    bool backspaceIsPressed() const;
    bool returnIsPressed() const;
    bool playerIsEnteringName() const;

};


#endif // _ENTER_HIGHSCORE_H_
