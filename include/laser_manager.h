#ifndef _LASER_MANAGER_H_
#define _LASER_MANAGER_H_

#include <memory>
#include <vector>

#include "laser.h"
#include "enemy.h"
#include "player.h"

namespace
{
    using lasers = std::vector<std::unique_ptr<Laser>>;
}

class LaserManager
{
public:
    lasers& getEnemyLasers();
    lasers& getPlayerLasers();
    void addEnemyLaser(const Point& pos, const Point& player_pos);
    void addPlayerLaser(const Point& pos);
    void checkCollisionPlayerLaser(Enemy& enemy);
    void update();
    
private:
    lasers enemy_lasers;
    lasers player_lasers;    
};


#endif // _LASER_MANAGER_H_
