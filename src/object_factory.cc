#include "object_factory.h"

#include <random>
#include <stdexcept>

#include "asset_manager.h"
#include "constants.h"
#include "point.h"
#include "texture.h"

namespace
{
    enum SpawnSections{UP, DOWN, LEFT, RIGHT};
    std::vector<std::pair<SpawnSections, int>> spawn_sections
    {
        {UP, SCREEN_WIDTH},
        {DOWN, SCREEN_WIDTH},
        {LEFT, SCREEN_HEIGHT},
        {RIGHT, SCREEN_HEIGHT}
    };
    
    Point getSpawnPoint(Texture* texture)
    {
        std::uniform_int_distribution<int> index(0,3);
        std::random_device rd;
    
        std::pair<SpawnSections, int> section{ spawn_sections.at( index(rd) ) };
        Point spawn_point;

        std::uniform_int_distribution<int> dist(0, section.second);

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

ObjectFactory& ObjectFactory::getInstance()
{
    static ObjectFactory instance;
    return instance;
}

std::unique_ptr<Enemy> ObjectFactory::createEnemy(const std::string& type)
{
    if (type == "asteroid") 
    {
        auto texture = AssetManager::getInstance().getTexture("asteroid");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Asteroid>(Asteroid(spawn_point));
    }
    else if (type == "blaster")
    {
        auto texture = AssetManager::getInstance().getTexture("blaster");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Blaster>(Blaster(spawn_point));
    }
    else if (type == "drone")
    {
        auto texture = AssetManager::getInstance().getTexture("drone");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Drone>(Drone(spawn_point));
    }
    else 
    {
        throw std::invalid_argument("Tried to create non-existing enemy " + type);
    }
}

std::unique_ptr<Laser> ObjectFactory::createLaser(const std::string& type,
                                                  const Point& pos,
                                                  const Point& destination)
{
    if (type == "player") 
    {
        double damage = 3;
        auto texture = AssetManager::getInstance().getTexture("player_laser");
        return std::make_unique<Laser>(texture, pos, destination, damage, 7);
    }
    else if (type == "enemy")
    {
        double damage = 1;
        auto texture = AssetManager::getInstance().getTexture("enemy_laser");
        return std::make_unique<Laser>(texture, pos, destination, damage, 2.5);
    }
    else 
    {
        throw std::invalid_argument("Tried to create non-existing laser type " + type);
    }
}
