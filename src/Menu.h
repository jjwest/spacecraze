#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <memory>

#include "GameState.h"
#include "Enums.h"
#include "Button.h"
#include "Text.h"


class Menu: public GameState
{
public:
    Menu();
    State getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    enum Buttons
    {
		NONE,
		PLAY,
		HIGHSCORE,
		OPTIONS,
		QUIT
    };
    int active_button = NONE;
    Button highscore_button;
    Button options_button;
    Button play_button;
    Button quit_button;
    SDL_Event event;
    State next_state = State::MENU;
    Text title;

    bool leftMouseButtonPressed() const;
};


#endif // _MENU_H_
