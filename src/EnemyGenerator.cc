#include "EnemyGenerator.h"

#include <random>

#include <SDL2/SDL.h>

#include "Asteroid.h"
#include "Blaster.h"
#include "Constants.h"
#include "Drone.h"
#include "ObjectFactory.h"

bool isMultiple(int a, int b)
{
    return a % b == 0;
}

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
    auto& factory = ObjectFactory::getInstance();
    for (int i = 0; i < enemy.spawn_amount; ++i)
    {
        world.addEnemy(factory.createEnemy(enemy.name));
    }
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
