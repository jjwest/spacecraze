#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "game_world.h"
#include "enemy.h"
#include "player.h"
#include "laser.h"
#include "laser_manager.h"
#include "enums.h"

class World: public GameWorld
{
public:
    World();
    bool playerDead() const;
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void render(SDL_Renderer* renderer);
    void update();

private:
    Player player;
    LaserManager laser_manager;
    std::vector<std::unique_ptr<Enemy>> enemies;

    void updateObjects();
    void resolveCollisions();
    void resolveLaserCollisions(Enemy& enemy);
    void resolveLaserCollisions(Player& player);
};


#endif // _WORLD_H_
