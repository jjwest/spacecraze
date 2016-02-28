#include "../include/object_factory.h"

#include "../include/asset_manager.h"
#include "../include/constants.h"
#include "../include/point.h"
#include "../include/texture.h"

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

ObjectFactory& ObjectFactory::getInstance()
{
    static ObjectFactory instance;
    return instance;
}

unique_ptr<Enemy> ObjectFactory::createEnemy(const string& type)
{
    if (type == "asteroid") 
    {
        auto texture = AssetManager::getInstance().getTexture("asteroid");
        auto spawn_point = getSpawnPoint(texture);
        return make_unique<Asteroid>(Asteroid(spawn_point));
    }
    else if (type == "blaster")
    {
        auto texture = AssetManager::getInstance().getTexture("blaster");
        auto spawn_point = getSpawnPoint(texture);
        return make_unique<Blaster>(Blaster(spawn_point));
    }
    else if (type == "drone")
    {
        auto texture = AssetManager::getInstance().getTexture("drone");
        auto spawn_point = getSpawnPoint(texture);
        return make_unique<Drone>(Drone(spawn_point));
    }
    else 
    {
        throw "Attempted to create non-existing enemy '" + type + "'";
    }
}

unique_ptr<Laser> ObjectFactory::createLaser(const string& type,
                                             const Point& pos,
                                             const Point& destination)
{
    if (type == "player") 
    {
        double damage = 3;
        auto texture = AssetManager::getInstance().getTexture("laser_friendly");
        return make_unique<Laser>(texture, pos, destination, damage, 5);
    }
    else if (type == "enemy")
    {
        double damage = 1;
        auto texture = AssetManager::getInstance().getTexture("laser_hostile");
        return make_unique<Laser>(texture, pos, destination, damage, 2.5);
    }
    else 
    {
        throw "Attempted to create non-existing laser '" + type + "'";
    }
}
