#ifndef _PLAY_H_
#define _PLAY_H_

#include <SDL2/SDL.h>
#include <memory>
#include <map>

#include "gamestate.h"
#include "player.h"
#include "laser_manager.h"
#include "enemy_generator.h"
#include "enemy_manager.h"
#include "enums.h"

class Play: public GameState
{
public:
    Play(SDL_Renderer* r);
    void handleEvents();
    void update();
    void render();
    GameStates nextState();

private:
    SDL_Event event;
    SDL_Renderer* renderer;
    GameStates next_state;

    EnemyGenerator enemy_generator;
    EnemyManager enemies;
    LaserManager lasers;
    Player player;
    std::map<std::string, bool> player_actions;

    void handleCollisions();
    void handleKeyPressed();
    void handleKeyReleased();
    void handleMousePressed();
    void handleMouseReleased();
};

#endif // _PLAY_H_
