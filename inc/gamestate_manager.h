#ifndef _GAMESTATE_MANAGER_H_
#define _GAMESTATE_MANAGER_H_

#include <vector>

#include "resourcemanager.h"
#include "enums.h"

class GamestateManager {
public:
    GamestateManager(SDL_Renderer*);
    ~GamestateManager();
    GameStates update();
    
private:
    GameStates gamestate;
    // MenuState menu;
    // HighscoreState highscore; 
    // std::vector<PlayState*> game;
    SDL_Event event;
    bool noActiveGame();
    void startNewGame();
    GameStates updateGame();
};


#endif // _GAMESTATE_MANAGER_H_
