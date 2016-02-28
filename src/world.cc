#include "../include/world.h"

#include <random>
#include <algorithm>
#include <iostream>

#include "../include/point.h"
#include "../include/constants.h"
#include "../include/asset_manager.h"
#include "../include/enums.h"



World::World() : GameWorld(), player{{500, 350}} {}

bool World::playerDead() const
{
    return player.isDead();
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::render(SDL_Renderer* renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    
    for (auto& enemy : enemies) 
    {
        enemy->draw(renderer);
    }

    auto& enemy_lasers = laser_manager.getEnemyLasers();
    for (auto& laser : enemy_lasers) 
    {
        laser->draw(renderer);
    }

    auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) 
    {
        laser->draw(renderer);
    }
    
    player.draw(renderer);
    SDL_RenderPresent(renderer);
}

void World::update()
{
    updateObjects();
    resolveCollisions();
}

void World::updateObjects()
{
    player.update(laser_manager);
    auto player_pos = player.getPos();

    for (auto& enemy : enemies) 
    {
        enemy->update(player_pos);
    }
    
    auto& enemy_lasers = laser_manager.getEnemyLasers();
    for (auto& laser : enemy_lasers) 
    {
        laser->update();
    }

    auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) 
    {
        laser->update();
    }
}

void World::resolveCollisions()
{
    auto player_aabb = player.getAABB();
    for (auto& enemy : enemies) 
    {
        if (enemy->collides(player_aabb)) 
        {
            player.reduceHealth(500);
            std::cout << "Collided with enemy" << std::endl;
            return;
        }
        resolveLaserCollisions(*enemy);
    }

    resolveLaserCollisions(player);
}

void World::resolveLaserCollisions(Enemy& enemy)
{
    auto enemy_aabb = enemy.getAABB();

    auto& player_lasers = laser_manager.getPlayerLasers();
    auto current_laser = begin(player_lasers);

    while (current_laser != end(player_lasers))
    {
        if ( (*current_laser)->collides(enemy_aabb) ) 
        {
            enemy.reduceHealth( (*current_laser)->getDamage() );
            current_laser = laser_manager.removePlayerLaser(current_laser);
        }
        else 
        {
            current_laser++;
        }
    }
}

void World::resolveLaserCollisions(Player& player)
{
    auto player_aabb = player.getAABB();

    auto& enemy_lasers = laser_manager.getEnemyLasers();
    auto current_laser = begin(enemy_lasers);

    while (current_laser != end(enemy_lasers))
    {
        if ( (*current_laser)->collides(player_aabb) ) 
        {
            std::cout << "Collided with laser" << std::endl;
            player.reduceHealth( (*current_laser)->getDamage() );
            current_laser = laser_manager.removeEnemyLaser(current_laser);
        }
        else 
        {
            current_laser++;
        }
    }
}
