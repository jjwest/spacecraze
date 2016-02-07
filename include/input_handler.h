#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL2/SDL.h>
#include <map>

#include "../inc/enums.h"

class InputHandler
{
public:
    InputHandler();
    GameStates update(GameStates gamestate);
    GameStates update(GameStates gamestate, 
                      std::map<std::string, bool>& player_actions);

private:
    SDL_Event event;

    void handleMousePressed(std::map<std::string, bool>& player_actions);
    void handleMouseReleased(std::map<std::string, bool>& player_actions);
    void handleKeyPressed(std::map<std::string, bool>& player_actions);
    void handleKeyReleased(std::map<std::string, bool>& player_actions);
};


#endif // _INPUT_HANDLER_H_
