#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <memory>

#include "gamestate.h"
#include "enums.h"
#include "button.h"
#include "sprite.h"

class Menu: public GameState
{
public:
    Menu(SDL_Renderer* renderer);
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);
    GameStates getNextState() const;

private:
    bool update_buttons = false;
    GameStates next_state;
    SDL_Event events;
    std::vector<std::unique_ptr<Sprite>> text; 
    std::vector<std::unique_ptr<Button>> buttons;
};


#endif // _MENU_H_
