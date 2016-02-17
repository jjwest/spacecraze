#ifndef _LASER_MANAGER_H_
#define _LASER_MANAGER_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "laser.h"

namespace
{
    using lasers = std::vector<std::unique_ptr<Laser>>;
}

class LaserManager
{
public:
    const lasers* getEnemyLasers() const;
    const lasers* getPlayerLasers() const;
    const lasers* removeEnemyLaser(lasers*);
    const lasers* removePlayerLaser(lasers*);
    void addEnemyLaser(const Point& pos, const Point& player_pos);
    void addPlayerLaser(const Point& pos);
    void draw(SDL_Renderer* renderer) const;
    void update();
    
private:
    lasers enemy_lasers;
    lasers player_lasers;    
};


#endif // _LASER_MANAGER_H_
