#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <map>
#include <iostream>

class Game 
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    void initSDL();
    void selectMusic();
    void loadMedia(); 
};

#endif
