#include "../include/enemy_manager.h"

#include <random>

#include "../include/texture.h"
#include "../include/asset_manager.h"
#include "../include/constants.h"

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

}

void EnemyManager::addAsteroid()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("asteroid");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Asteroid> asteroid(new Asteroid(spawn_point));
    asteroids.push_back( move(asteroid) );
}

void EnemyManager::addBlaster()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("blaster");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Blaster> blaster(new Blaster(spawn_point));
    blasters.push_back( move(blaster) );    
}

void EnemyManager::addDrone()
{
    auto& assets = AssetManager::getInstance();
    auto texture = assets.getTexture("drone");
    auto spawn_point = getSpawnPoint(texture);
    unique_ptr<Drone> drone(new Drone(spawn_point));
    drones.push_back( move(drone) );    
}

void EnemyManager::update(const Point& player_pos, LaserManager& laser_manager)
{
    for (auto& i : asteroids) 
    {
        i->update();
    }
    for (auto& i : blasters) 
    {
        i->update(player_pos, laser_manager);
    }
    for (auto& i : drones) 
    {
        i->update(player_pos);
    }
}

