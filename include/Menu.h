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
    Button play_button;
    Button highscore_button;
    Button options_button;
    Button quit_button;
    State next_state = State::MENU;
    SDL_Event event;
    Text title;

    bool leftMouseButtonPressed() const;
};


#endif // _MENU_H_
