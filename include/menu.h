#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <memory>

#include "game_state.h"
#include "enums.h"
#include "button.h"
#include "rendered_text.h"

class Menu: public GameState
{
public:
    Menu(SDL_Renderer* renderer);
    State getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    bool check_button_pressed = false;
    State next_state;
    SDL_Event events;
    RenderedText title;
    std::vector<std::unique_ptr<Button>> buttons;
};


#endif // _MENU_H_
