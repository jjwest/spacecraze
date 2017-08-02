#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <memory>

#include "GameState.h"
#include "ScoreKeeper.h"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    ScoreKeeper score;
    State current_state_id = State::MENU;
    bool running = true;
    std::unique_ptr<GameState> current_state;

    void initSDL() const;
    void createWindowAndRenderer();
    void loadAssets() const;
    void shutdownSDL() const;
    void sleepIfFrameTooFast(Uint32 start, Uint32 end) const;
    void changeStateIfRequired(State next_state);
};

#endif
