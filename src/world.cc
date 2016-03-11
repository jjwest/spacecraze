#include "world.h"

#include <iostream>

#include "point.h"
#include "constants.h"
#include "asset_manager.h"
#include "enums.h"

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
    auto current_enemy = begin(enemies);

    while (current_enemy != end(enemies))
    {
        if ( (*current_enemy)->collides(player_aabb)) 
        {
            player.reduceHealth(500);
            return;
        }

        resolveLaserCollisions(**current_enemy);

        if ( (*current_enemy)->isDead() ) 
        {
            current_enemy = enemies.erase(current_enemy);
        }
        else 
        {
            current_enemy++;
        }
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
            player.reduceHealth( (*current_laser)->getDamage() );
            current_laser = laser_manager.removeEnemyLaser(current_laser);
        }
        else 
        {
            current_laser++;
        }
    }
}
