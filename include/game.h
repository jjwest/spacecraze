#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>

#include "game_state.h"

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
    State current_state_id;

    void initSDL();
    void selectMusic();
    void loadMedia();
    void changeState(State next_state_id);
};

#endif
