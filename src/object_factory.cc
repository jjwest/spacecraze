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
	SDL_Rect hitbox {
	    spawn_point.x,
		spawn_point.y,
		texture->getWidth(),
		texture->getHeight()
	 };
        return std::make_unique<Asteroid>(Asteroid(hitbox));
    }
    else if (type == "blaster")
    {
        auto texture = Assets::getInstance().getTexture("blaster");
        auto spawn_point = getSpawnPoint(texture);
	SDL_Rect hitbox {
	    spawn_point.x,
		spawn_point.y,
		texture->getWidth(),
		texture->getHeight()
	 };
        return std::make_unique<Blaster>(Blaster(hitbox));
    }
    else if (type == "drone")
    {
	float scale = 0.5;
        auto texture = Assets::getInstance().getTexture("drone");
        auto spawn_point = getSpawnPoint(texture);
	SDL_Rect hitbox {
	    spawn_point.x,
		spawn_point.y,
		static_cast<int>(texture->getWidth() * scale),
		static_cast<int>(texture->getHeight() * scale)
	 };
        return std::make_unique<Drone>(Drone(hitbox));
    }
    else
    {
        throw std::invalid_argument("Tried to create non-existing enemy " + type);
    }
}

std::unique_ptr<Laser> ObjectFactory::createEnemyLaser(
    const Point& origin,
    const Point& destination,
    double damage)
{
    auto texture = Assets::getInstance().getTexture("enemy_laser");
    return std::make_unique<Laser>(texture, origin, destination, damage, 2.5);
}

std::unique_ptr<Laser> ObjectFactory::createPlayerLaser(
    const Point& origin,
    const Point& destination,
    double damage)
{
    auto texture = Assets::getInstance().getTexture("player_laser");
    return std::make_unique<Laser>(texture, origin, destination, damage, 7);
}
