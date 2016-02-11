#ifndef _LASER_MANAGER_H_
#define _LASER_MANAGER_H_

#include <memory>
#include <vector>

#include "laser.h"
#include "enemy.h"
#include "player.h"

class LaserManager
{
public:
    LaserManager();
    void addEnemyLaser(const Point& pos, const Point& player_pos);
    void addPlayerLaser(const Point& pos);
    void handleCollissionEnemyLaser(Player& player);
    void handleCollissionPlayerLaser(Enemy& enemy);
    
private:
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;    
};


#endif // _LASER_MANAGER_H_
