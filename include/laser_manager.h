#ifndef _PROJECTILE_MANAGER_H
#define _PROJECTILE_MANAGER_H

#include <vector>
#include <memory>

#include "laser.h"
#include "point.h"

namespace laser
{
    using vec = std::vector<std::unique_ptr<Laser>>;
}

class LaserManager
{
public:
    LaserManager();
    const laser::vec& getEnemyLasers() const;
    const laser::vec& getPlayerLasers() const;
    void addEnemyLaser(const Point& pos, const Point& dest, double dmg);
    void addPlayerLaser(const Point& pos, double dmg);
    void updateLasers();
    void removeDeadLasers();

private:
    laser::vec enemy_lasers;
    laser::vec player_lasers;
};


#endif // _PROJECTILE_MANAGER_H
