#include "../include/laser_manager.h"
#include "../include/object_factory.h"

#include <SDL2/SDL.h>

LaserManager::LaserManager() {}

const laser::vec& LaserManager::getEnemyLasers() const
{
    return enemy_lasers;
}

const laser::vec& LaserManager::getPlayerLasers() const
{
    return player_lasers;
}

void LaserManager::addEnemyLaser(const Point& pos, const Point& dest)
{
    auto& factory = ObjectFactory::getInstance();
    enemy_lasers.push_back(factory.createLaser("enemy", pos, dest));
}

void LaserManager::addPlayerLaser(const Point& pos)
{
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);

    auto& factory = ObjectFactory::getInstance();
    player_lasers.push_back(factory.createLaser("player", pos, destination));
}

laser::vec::const_iterator LaserManager::removeEnemyLaser(laser::vec::const_iterator it)
{
    return enemy_lasers.erase(it);
}

laser::vec::const_iterator LaserManager::removePlayerLaser(laser::vec::const_iterator it)
{
    return player_lasers.erase(it);
}
