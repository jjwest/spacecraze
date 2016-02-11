#include "../include/laser_manager.h"
#include "../include/asset_manager.h"
#include "../include/texture.h"
#include "../include/aabb.h"

using namespace std;

namespace
{
    using itr = vector<unique_ptr<Laser>>::iterator;
    
    bool collides(const Player& player, itr laser)
    {
        AABB player_aabb = player.getAABB();
        AABB laser_aabb = (*laser)->getAABB();

        return player_aabb.intersect(laser_aabb);
    }
    
    bool collides(const Enemy& enemy, itr laser)
    {
        AABB enemy_aabb = enemy.getAABB();
        AABB laser_aabb = (*laser)->getAABB();

        return enemy_aabb.intersect(laser_aabb);
    }
}

LaserManager::LaserManager()
    : enemy_lasers{}, player_lasers{} {}

void LaserManager::addEnemyLaser(const Point& pos, const Point& player_pos)
{
    Texture* texture = AssetManager::getInstance().getTexture("hostile_laser");
    unique_ptr<Laser> laser(new Laser(texture, pos, player_pos, 3));
    enemy_lasers.push_back( move(laser) );
}

void LaserManager::addPlayerLaser(const Point& pos)
{
    Texture* texture = AssetManager::getInstance().getTexture("friendly_laser");
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);
    unique_ptr<Laser> laser(new Laser(texture, pos, destination, 3));
    player_lasers.push_back( move(laser) );
}

void LaserManager::handleCollissionEnemyLaser(Player& player)
{
    auto laser = begin(enemy_lasers);   
    while (laser != end(enemy_lasers))
    {
        if (collides(player, laser))
        {
            player.reduceHealth((*laser)->getDamage());
            laser = enemy_lasers.erase(laser);
        }
        else
        {
            laser++;
        }
    }
}

void LaserManager::handleCollissionPlayerLaser(Enemy& enemy)
{
    auto laser = begin(player_lasers);   
    while (laser != end(player_lasers))
    {
        if (collides(enemy, laser))
        {
            enemy.reduceHealth((*laser)->getDamage());
            laser = player_lasers.erase(laser);
        }
        else
        {
            laser++;
        }
    }
}
