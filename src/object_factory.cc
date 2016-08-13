#include "object_factory.h"

#include <random>
#include <stdexcept>

#include "asset_manager.h"
#include "constants.h"
#include "point.h"
#include "texture.h"

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

    switch (section.first) {
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

double getLaserAngle(const Point& pos, int width, int height)
{
    int x, y;
    SDL_GetMouseState(&x,&y);

    int center_x = pos.x + (width / 2);
    int center_y = pos.y + (height / 2);

    double angle = atan2(center_y - y, center_x - x);
    angle = angle * 180 / M_PI;

    return angle - 90 % 360;
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

std::unique_ptr<Laser> ObjectFactory::createEnemyLaser(const Point& origin,
						       const Point& destination,
						       double damage)
{
    auto texture = AssetManager::getInstance().getTexture("enemy_laser");
    double angle = getLaserAngle(origin, texture->getWidth(), texture->getHeight());
    return std::make_unique<Laser>(texture, origin, destination, damage, 2.5, angle);
}

std::unique_ptr<Laser> ObjectFactory::createPlayerLaser(const Point& origin,
							const Point& destination,
							double damage)
{
    auto texture = AssetManager::getInstance().getTexture("player_laser");
    double angle = getLaserAngle(origin, texture->getWidth(), texture->getHeight());
    return std::make_unique<Laser>(texture, origin, destination, damage, 7, angle);
}
