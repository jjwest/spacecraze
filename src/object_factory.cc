#include "object_factory.h"

#include <random>
#include <stdexcept>

#include "assets.h"
#include "constants.h"
#include "enums.h"
#include "point.h"
#include "texture.h"

ObjectFactory& ObjectFactory::getInstance()
{
    static ObjectFactory instance;
    return instance;
}

Point getSpawnPoint(Texture* texture)
{
    std::vector<std::pair<Sections, int>> spawn_sections
    {
	{Section_Up, SCREEN_WIDTH},
	{Section_Down, SCREEN_WIDTH},
	{Section_Left, SCREEN_HEIGHT},
	{Section_Right, SCREEN_HEIGHT}
    };

    std::uniform_int_distribution<int> index(0,3);
    std::random_device random;

    std::pair<Sections, int> section{ spawn_sections.at( index(random) ) };
    std::uniform_int_distribution<int> spawn_range(0, section.second);

    Point spawn_point;
    switch (section.first) {
    case Section_Up:
        spawn_point = {spawn_range(random), 0 - texture->getHeight()};
        break;

    case Section_Left:
        spawn_point = {0 - texture->getWidth(), spawn_range(random)};
        break;

    case Section_Down:
        spawn_point = {spawn_range(random), SCREEN_HEIGHT};
        break;

    case Section_Right:
        spawn_point = {SCREEN_WIDTH, spawn_range(random)};
        break;
    }

    return spawn_point;
}


std::unique_ptr<Enemy> ObjectFactory::createEnemy(const std::string& type)
{
    if (type == "asteroid")
    {
        auto texture = Assets::getInstance().getTexture("asteroid");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Asteroid>(Asteroid(spawn_point));
    }
    else if (type == "blaster")
    {
        auto texture = Assets::getInstance().getTexture("blaster");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Blaster>(Blaster(spawn_point));
    }
    else if (type == "drone")
    {
        auto texture = Assets::getInstance().getTexture("drone");
        auto spawn_point = getSpawnPoint(texture);
        return std::make_unique<Drone>(Drone(spawn_point));
    }
    else
    {
        throw std::invalid_argument("Tried to create non-existing enemy " + type);
    }
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

std::unique_ptr<Laser> ObjectFactory::createEnemyLaser(const Point& origin,
						       const Point& destination,
						       double damage)
{
    auto texture = Assets::getInstance().getTexture("enemy_laser");
    double angle = getLaserAngle(origin, texture->getWidth(), texture->getHeight());
    return std::make_unique<Laser>(texture, origin, destination, damage, 2.5, angle);
}

std::unique_ptr<Laser> ObjectFactory::createPlayerLaser(const Point& origin,
							const Point& destination,
							double damage)
{
    auto texture = Assets::getInstance().getTexture("player_laser");
    double angle = getLaserAngle(origin, texture->getWidth(), texture->getHeight());
    return std::make_unique<Laser>(texture, origin, destination, damage, 7, angle);
}
