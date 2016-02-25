#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "laser.h"
#include "enums.h"

class World
{
public:
    World();
    void addEnemyLaser(const Point& pos);
    void addPlayerLaser(const Point& pos);
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void render(SDL_Renderer* renderer);
    void update();

private:
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;
    
    void updateObjects();
    void handleCollisions();
};


#endif // _WORLD_H_
