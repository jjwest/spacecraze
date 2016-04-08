#include "enemy_generator.h"

#include <SDL2/SDL.h>
#include <random>

#include "constants.h"
#include "asteroid.h"
#include "blaster.h"
#include "drone.h"
#include "object_factory.h"

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
    for (auto& enemy : enemy_types) {
        if (readyToSpawn(enemy)) {
            spawnEnemy(world, enemy);
            updateEnemyType(enemy);
        }
    }
}

bool EnemyGenerator::readyToSpawn(const EnemyType& enemy)
{
    auto current_time = SDL_GetTicks();
    return current_time - enemy.last_time_spawned > enemy.spawn_delay * 1000;
}

void EnemyGenerator::updateEnemyType(EnemyType& enemy)
{
    auto current_time = SDL_GetTicks();
    enemy.times_spawned += 1;
    enemy.last_time_spawned = current_time;

    if (isMultiple(enemy.times_spawned, enemy.spawns_until_decreased_delay)) {
        enemy.spawn_delay *= 0.90;
    }
}

void EnemyGenerator::spawnEnemy(World& world, const EnemyType& enemy)
{
    auto& factory = ObjectFactory::getInstance();
    for (int i = 0; i < enemy.spawn_amount; ++i) {
        world.addEnemy(factory.createEnemy(enemy.name));
    }
}
