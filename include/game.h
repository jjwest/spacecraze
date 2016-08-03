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
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unique_ptr<GameState> current_state;
    States current_state_id = State_Menu;

    void initSDL();
    void createWindowAndRenderer();
    void loadAssets();
    void freeLoadedAssets();
    void shutdownSDL();
    bool stillPlaying() const;
    void sleepIfFrameTooFast(Uint32 time_elapsed) const;
    void setInitialStateToMenu();
    void switchCurrentStateIfChanged(States next_state_id);
};

#endif
