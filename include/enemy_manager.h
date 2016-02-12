#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include <memory>
#include <vector>

#include "enemy.h"
#include "asteroid.h"
#include "blaster.h"
#include "drone.h"
#include "player.h"

class EnemyManager
{
public:
    EnemyManager() {};
    void addAsteroid();
    void addBlaster();
    void addDrone();
    void update(const Point& player_pos, LaserManager& laser_manager);
    void checkCollisions(Player& player);

private:
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Blaster>> blasters;
    std::vector<std::unique_ptr<Drone>> drones;
};

#endif // _ENEMY_MANAGER_H_
