#include "laser_manager.h"
#include "object_factory.h"

#include <SDL2/SDL.h>
#include <algorithm>

LaserManager::LaserManager() {}

const laser::vec& LaserManager::getEnemyLasers() const
{
    return enemy_lasers;
}

const laser::vec& LaserManager::getPlayerLasers() const
{
    return player_lasers;
}

void LaserManager::addEnemyLaser(const Point& pos, const Point& dest, double dmg)
{
    auto& factory = ObjectFactory::getInstance();
    enemy_lasers.push_back(factory.createLaser("enemy", pos, dest, dmg));
}

void LaserManager::addPlayerLaser(const Point& pos, double dmg)
{
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);

    auto& factory = ObjectFactory::getInstance();
    player_lasers.push_back(factory.createLaser("player", pos, destination, dmg));
}

void LaserManager::removeDeadLasers()
{
    
    enemy_lasers.erase(std::remove_if(begin(enemy_lasers),
                                      end(enemy_lasers),
                                      [] (auto& l) { return l->isDead(); }),
                                      end(enemy_lasers));
    
    player_lasers.erase(std::remove_if(begin(player_lasers),
                                       end(player_lasers),
                                       [] (auto& l) { return l->isDead(); }),
                                       end(player_lasers));
}

void LaserManager::updateLasers()
{
    for (auto& laser : player_lasers) {
	laser->update();
    }
    for (auto& laser : enemy_lasers) {
	laser->update();
    }
}
