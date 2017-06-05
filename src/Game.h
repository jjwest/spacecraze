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

    void initSDL() const;
    void createWindowAndRenderer();
    void loadAssets() const;
    void shutdownSDL() const;
    void sleepIfFrameTooFast(Uint32 start, Uint32 end) const;
};

#endif
