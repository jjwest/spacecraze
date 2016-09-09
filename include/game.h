#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void initSDL();
    void createWindowAndRenderer();
    void destroyWindowAndRenderer();
    void loadAssets();
    void freeLoadedAssets();
    void shutdownSDL();
    void sleepIfFrameTooFast(Uint32 time_elapsed) const;
};

#endif
