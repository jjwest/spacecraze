#include "EnemyGenerator.h"

#include <random>

#include <SDL2/SDL.h>

#include "Asteroid.h"
#include "AssetManager.h"
#include "Blaster.h"
#include "Constants.h"
#include "Drone.h"



EnemyGenerator::EnemyGenerator()
{
    enemy_types.push_back({ "asteroid", 5, 2, 4 });
    enemy_types.push_back({ "blaster", 10, 2, 5 });
    enemy_types.push_back({ "drone", 2.5, 3, 4 });
}

inline bool isMultiple(int a, int b)
{
    return a % b == 0;
}

void EnemyGenerator::update(World& world)
{
    for (auto& enemy : enemy_types)
    {
        if (readyToSpawn(enemy))
		{
			for (int i = 0; i < enemy.spawn_amount; ++i)
			{
				world.addEnemy(createEnemy(enemy.name));
			}

			++enemy.waves_spawned;
			enemy.last_time_spawned = SDL_GetTicks();

			if (isMultiple(enemy.waves_spawned, enemy.spawns_until_increased_spawn_rate))
			{
				++enemy.spawn_amount;
			}
        }
    }
}

bool EnemyGenerator::readyToSpawn(const EnemyType& enemy)
{
    Uint32 current_time = SDL_GetTicks();
    return current_time - enemy.last_time_spawned > enemy.spawn_delay * 1000;
}


Point getSpawnPoint(Texture* texture)
{
    enum Section {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NUM_SECTIONS
    };

    static std::random_device random;
    static std::uniform_int_distribution<int> section(0, NUM_SECTIONS);
    static std::uniform_int_distribution<int> spawn_range_x(200, SCREEN_WIDTH - 200);
    static std::uniform_int_distribution<int> spawn_range_y(200, SCREEN_HEIGHT - 200);

    Point spawn_point;
    switch (section(random))
    {
    case DOWN:  spawn_point = { spawn_range_x(random), SCREEN_HEIGHT }; break;
    case UP:    spawn_point = { spawn_range_x(random), 0 - texture->getHeight() }; break;
    case RIGHT: spawn_point = { SCREEN_WIDTH, spawn_range_y(random) };  break;
    case LEFT:  spawn_point = { 0 - texture->getWidth(), spawn_range_y(random) };  break;
    }

    return spawn_point;
}

std::unique_ptr<Enemy> EnemyGenerator::createEnemy(const std::string& type)
{
    if (type == "asteroid")
    {
        auto texture = AssetManager::instance().getTexture("asteroid");
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
        auto texture = AssetManager::instance().getTexture("blaster");
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
        auto texture = AssetManager::instance().getTexture("drone");
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
