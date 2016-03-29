#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "laser.h"
#include "laser_manager.h"
#include "enums.h"

class World
{
public:
    World();
    bool playerIsDead() const;
    int getScore() const;
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void usePlayerSpecial();
    void render(SDL_Renderer* renderer);
    void update();

private:
    Player player;
    LaserManager laser_manager;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int score = 0;

    void updateObjects();
    void updateScore();
    void resolveCollisions();
    void removeDeadObjects();
};

#endif // _WORLD_H_
