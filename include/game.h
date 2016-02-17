#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <map>
#include <iostream>

#include "gamestate.h"

class Game 
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameState* current_state;
    GameStates current_state_id;
    void initSDL();
    void selectMusic();
    void loadMedia();
    void changeState(GameStates next_state);
};

#endif
