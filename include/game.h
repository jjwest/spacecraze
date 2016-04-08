#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>

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
    std::unique_ptr<GameState> current_state;
    GameStates current_state_id;

    void initSDL();
    void selectMusic();
    void loadMedia();
    void changeState(GameStates next_state_id);
};

#endif
