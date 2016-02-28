#ifndef _LASER_MANAGER_H_
#define _LASER_MANAGER_H_

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
    void addEnemyLaser(const Point& pos, const Point& dest);
    void addPlayerLaser(const Point& pos);
    laser::vec::const_iterator removeEnemyLaser(laser::vec::const_iterator it);
    laser::vec::const_iterator removePlayerLaser(laser::vec::const_iterator it);

private:
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;
};


#endif // _LASER_MANAGER_H_
