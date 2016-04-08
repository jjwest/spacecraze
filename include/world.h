#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "laser.h"
#include "laser_manager.h"
#include "user_interface.h"
#include "enums.h"

class World
{
public:
    World(SDL_Renderer* renderer);
    bool playerIsDead() const;
    int getScore() const;
    void update();
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void usePlayerSpecial();
    void render(SDL_Renderer* renderer);

private:
    Player player;
    LaserManager laser_manager;
    UserInterface user_interface;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int score = 0;

    void updateScore();
    void updateObjects();
    void resolveCollisions();
    void removeDeadObjects();
};

#endif // _WORLD_H_
