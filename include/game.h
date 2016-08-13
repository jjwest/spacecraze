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

    bool stillPlaying() const;
    void initSDL();
    void createWindowAndRenderer();
    void destroyWindowAndRenderer();
    void loadAssets();
    void freeLoadedAssets();
    void shutdownSDL();
    void sleepIfFrameTooFast(Uint32 time_elapsed) const;
    void setStateToMenu();
    void changeCurrentStateIfNew(States next_state_id);
};

#endif
