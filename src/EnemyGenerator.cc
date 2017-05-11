#include "EnemyGenerator.h"

#include <random>

#include <SDL2/SDL.h>

#include "Asteroid.h"
#include "AssetManager.h"
#include "Blaster.h"
#include "Constants.h"
#include "Drone.h"

enum class Section {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


EnemyGenerator::EnemyGenerator()
{
    enemy_types.push_back({ "asteroid", 5, 2, 4 });
    enemy_types.push_back({ "blaster", 10, 2, 5 });
    enemy_types.push_back({ "drone", 2.5, 3, 4 });
}

void EnemyGenerator::update(World& world)
{
    for (auto& enemy : enemy_types)
    {
        if (readyToSpawn(enemy))
	{
            spawnEnemy(world, enemy);
            updateEnemyType(enemy);
        }
    }
}

bool EnemyGenerator::readyToSpawn(const EnemyType& enemy)
{
    Uint32 current_time = SDL_GetTicks();
    return current_time - enemy.last_time_spawned > enemy.spawn_delay * 1000;
}

void EnemyGenerator::spawnEnemy(World& world, const EnemyType& enemy)
{
    for (int i = 0; i < enemy.spawn_amount; ++i)
    {
        world.addEnemy(createEnemy(enemy.name));
    }
}

Point getSpawnPoint(Texture* texture)
{
    std::vector<std::pair<Section, int>> spawn_sections {
	{Section::UP, SCREEN_WIDTH},
	{Section::DOWN, SCREEN_WIDTH},
	{Section::LEFT, SCREEN_HEIGHT},
	{Section::RIGHT, SCREEN_HEIGHT}
    };

    std::uniform_int_distribution<int> index(0,3);
    std::random_device random;

    std::pair<Section, int> section{ spawn_sections.at( index(random) ) };
    std::uniform_int_distribution<int> spawn_range(0, section.second);

    Point spawn_point;
    switch (section.first)
    {
    case Section::UP:    spawn_point = { spawn_range(random), 0 - texture->getHeight() }; break;
    case Section::LEFT:  spawn_point = { 0 - texture->getWidth(), spawn_range(random) };  break;
    case Section::DOWN:  spawn_point = { spawn_range(random), SCREEN_HEIGHT }; break;
    case Section::RIGHT: spawn_point = { SCREEN_WIDTH, spawn_range(random) };  break;
    }

    return spawn_point;
}

std::unique_ptr<Enemy> EnemyGenerator::createEnemy(const std::string& type)
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

inline bool isMultiple(int a, int b)
{
    return a % b == 0;
}

void EnemyGenerator::updateEnemyType(EnemyType& enemy)
{
    enemy.times_spawned += 1;
    enemy.last_time_spawned = SDL_GetTicks();

    if (isMultiple(enemy.times_spawned, enemy.spawns_until_increased_spawn_rate))
    {
	enemy.spawn_amount++;
    }
}
