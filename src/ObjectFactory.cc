#include "ObjectFactory.h"

#include <random>
#include <stdexcept>

#include "AssetManager.h"
#include "Constants.h"
#include "Enums.h"
#include "Point.h"
#include "Texture.h"

enum Sections{Section_Up, Section_Down, Section_Left, Section_Right};

ObjectFactory& ObjectFactory::getInstance()
{
    static ObjectFactory instance;
    return instance;
}

Point getSpawnPoint(Texture* texture)
{
    std::vector<std::pair<Sections, int>> spawn_sections
    {
	{Section_Up, constants::SCREEN_WIDTH},
	{Section_Down, constants::SCREEN_WIDTH},
	{Section_Left, constants::SCREEN_HEIGHT},
	{Section_Right, constants::SCREEN_HEIGHT}
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
        spawn_point = {spawn_range(random), constants::SCREEN_HEIGHT};
        break;

    case Section_Right:
        spawn_point = {constants::SCREEN_WIDTH, spawn_range(random)};
        break;
    }

    return spawn_point;
}


std::unique_ptr<Enemy> ObjectFactory::createEnemy(const std::string& type)
{
    if (type == "asteroid")
    {
        auto texture = AssetManager::getInstance().getTexture("asteroid");
        auto spawn_point = getSpawnPoint(texture);
	SDL_Rect hitbox {
	    spawn_point.x,
	    spawn_point.y,
	    texture->getWidth(),
	    texture->getHeight()
	 };
        return std::make_unique<Asteroid>(hitbox);
    }
    else if (type == "blaster")
    {
        auto texture = AssetManager::getInstance().getTexture("blaster");
        auto spawn_point = getSpawnPoint(texture);
	SDL_Rect hitbox {
	    spawn_point.x,
	    spawn_point.y,
	    texture->getWidth(),
	    texture->getHeight()
	 };

        return std::make_unique<Blaster>(hitbox);
    }
    else if (type == "drone")
    {
	float scale = 0.5;
        auto texture = AssetManager::getInstance().getTexture("drone");
        auto spawn_point = getSpawnPoint(texture);
	SDL_Rect hitbox {
	    spawn_point.x,
	    spawn_point.y,
	    static_cast<int>(texture->getWidth() * scale),
	    static_cast<int>(texture->getHeight() * scale)
	 };

        return std::make_unique<Drone>(hitbox);
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
    auto texture = AssetManager::getInstance().getTexture("enemy_laser");
    double speed = 2.5;
    return std::make_unique<Laser>(texture, origin, destination, damage, speed);
}

std::unique_ptr<Laser> ObjectFactory::createPlayerLaser(
    const Point& origin,
    const Point& destination,
    double damage)
{
    auto texture = AssetManager::getInstance().getTexture("player_laser");
    double speed = 7.0;
    return std::make_unique<Laser>(texture, origin, destination, damage, speed);
}
