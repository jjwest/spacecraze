#include "../include/world.h"

#include <random>
#include <algorithm>

#include "../include/constants.h"
#include "../include/asset_manager.h"

using namespace std;

namespace
{
    enum SpawnSections{UP, DOWN, LEFT, RIGHT};
    vector<pair<SpawnSections, int>> spawn_sections
    {
        {UP, SCREEN_WIDTH},
        {DOWN, SCREEN_WIDTH},
        {LEFT, SCREEN_HEIGHT},
        {RIGHT, SCREEN_HEIGHT}
    };
    
    Point getSpawnPoint(Texture* texture)
    {
        uniform_int_distribution<int> index(0,3);
        random_device rd;
    
        pair<SpawnSections, int> section{ spawn_sections.at( index(rd) ) };
        Point spawn_point;

        uniform_int_distribution<int> dist(0, section.second);

        switch (section.first)
        {
        case UP:
            spawn_point = {dist(rd), 0 - texture->getHeight()};
            break;
            
        case LEFT:
            spawn_point = {0 - texture->getWidth(), dist(rd)};
            break;
        
        case DOWN:
            spawn_point = {dist(rd), SCREEN_HEIGHT};
            break;

        case RIGHT:
            spawn_point = {SCREEN_WIDTH, dist(rd)};
            break;
        }

        return spawn_point;
    }

    template<class TYPE>
    void collisionCheckEnemy(TYPE enemy, TYPE end, Player& player)
    {
        auto player_aabb = player.getAABB();
        while (enemy != end)
        {
            auto enemy_aabb = (*enemy)->getAABB();
            if (player_aabb.intersect(enemy_aabb)) 
            {
                player.reduceHealth(500);
                break;
            }
        }
    }
}

World::World()
    : player{{500, 350}} {}

void World::addAsteroid()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("asteroid");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Asteroid> asteroid(new Asteroid(spawn_point));
    asteroids.push_back( move(asteroid) );
}

void World::addBlaster()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("blaster");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Blaster> blaster(new Blaster(spawn_point));
    blasters.push_back( move(blaster) );    
}

void World::addDrone()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("drone");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Drone> drone(new Drone(spawn_point));
    drones.push_back( move(drone) );    
}

void World::update(const map<string, bool>& player_actions)
{
    updateObjects(player_actions);
    handleCollisions();
}

void World::updateObjects(const map<string, bool>& player_actions)
{
    player.update(player_actions);
    
    for (auto& i : asteroids)
    {
        i->update();
    }
    for (auto& i : blasters) 
    {
        i->update(player.getPos(), lasers);
    }
    for (auto& i : drones) 
    {
        i->update(player.getPos());
    }

    lasers.update();
}

void World::handleCollisions()
{
    collisionCheckEnemy(begin(asteroids), end(asteroids), player);
    collisionCheckEnemy(begin(blasters), end(blasters), player);
    collisionCheckEnemy(begin(drones), end(drones), player);

    
}
