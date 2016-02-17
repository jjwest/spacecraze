#include "../include/laser_manager.h"
#include "../include/asset_manager.h"
#include "../include/texture.h"
#include "../include/aabb.h"

const lasers* LaserManager::getEnemyLasers() const
{
    return &enemy_lasers;
}

const lasers* LaserManager::getPlayerLasers() const
{
    return &player_lasers;
}

void LaserManager::addEnemyLaser(const Point& pos, const Point& player_pos)
{
    Texture* texture = AssetManager::getInstance().getTexture("laser_hostile");
    std::unique_ptr<Laser> laser(new Laser(texture, pos, player_pos, 3));
    enemy_lasers.push_back( move(laser) );
}

void LaserManager::addPlayerLaser(const Point& pos)
{
    Texture* texture = AssetManager::getInstance().getTexture("laser_friendly");
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);
    std::unique_ptr<Laser> laser(new Laser(texture, pos, destination, 3));
    player_lasers.push_back( move(laser) );
}

void LaserManager::draw(SDL_Renderer* renderer) const
{
    for (auto& i : enemy_lasers) 
    {
        i->draw(renderer);
    }
    for (auto& i : player_lasers) 
    {
        i->draw(renderer);
    }
}

void LaserManager::update()
{
    for (auto& i : enemy_lasers) 
    {
        i->update();
    }
    for (auto& i : player_lasers) 
    {
        i->update();
    }
}
