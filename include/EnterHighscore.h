#ifndef _ENTER_HIGHSCORE_H_
#define _ENTER_HIGHSCORE_H_

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

#include "Button.h"
#include "GameState.h"
#include "Enums.h"
#include "RenderedText.h"
#include "ScoreKeeper.h"

class EnterHighscore: public GameState
{
public:
    EnterHighscore(SDL_Renderer* renderer, const ScoreKeeper& score);
    ~EnterHighscore();
    State getNextState() const override;
    void draw(SDL_Renderer* renderer) override;
    void handleEvents() override;
    void update() override;
private:
    Button back_button;
    int player_score;
    SDL_Event event;
    State next_state = State::ENTER_HIGHSCORE;
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
