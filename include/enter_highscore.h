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
#include "score_keeper.h"

class EnterHighscore: public GameState
{
public:
    EnterHighscore(SDL_Renderer* renderer, const ScoreKeeper& score);
    ~EnterHighscore();
    States getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;
private:
    Button back_button;
    int player_score;
    SDL_Event event;
    States next_state = State_EnterHighscore;
    std::string player_name;
    std::unique_ptr<RenderedText> rendered_player_name;

    void renderUserInput(SDL_Renderer* renderer);
    bool goodEnoughForHighscore(int score) const;
    bool leftMouseButtonPressed() const;
    bool specialKeyPressed() const;
    bool backspaceIsPressed() const;
    bool returnIsPressed() const;
    void updateHighscoreFile() const;
    bool enteringName() const;
    bool containsSpace(const std::string& input) const;
};


#endif // _ENTER_HIGHSCORE_H_
