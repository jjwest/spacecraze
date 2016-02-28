#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include <SDL2/SDL.h>
#include <memory>

#include "enemy.h"
#include "point.h"

class GameWorld
{
public:
    GameWorld() {};
    virtual ~GameWorld() {};
    virtual bool playerDead() const = 0;
    virtual void addEnemy(std::unique_ptr<Enemy> enemy) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;
};


#endif // _GAME_WORLD_H_
