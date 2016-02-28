#include "../include/enemy_generator.h"

#include <SDL2/SDL.h>

#include "../include/constants.h"

using namespace std;

namespace
{
    bool isMultiple(int a, int b)
    {
        return a % b == 0;
    }
}

EnemyGenerator::EnemyGenerator()
{
    enemy_types.push_back( EnemyType{"asteroid", 4, 2, 2, 4} );
    enemy_types.push_back( EnemyType{"blaster", 10, 2, 2, 5} );
    enemy_types.push_back( EnemyType{"drone", 2, 3, 2, 4} );
 }

void EnemyGenerator::update(GameWorld& world)
{
    for (auto& enemy : enemy_types) 
    {
        auto current_time = SDL_GetTicks();
        if (readyToSpawn(enemy, current_time)) 
        {
            spawnEnemy(world, enemy);
            enemy.num_times_spawned += 1;
            enemy.last_time_spawned = current_time;

            if (isMultiple(enemy.num_times_spawned,
                           enemy.spawns_until_decreased_delay))
            {
                enemy.spawn_delay *= 0.85;
            }
        }
    }
}

bool EnemyGenerator::readyToSpawn(const EnemyType& enemy, Uint32 current_time)
{
    return current_time - enemy.last_time_spawned > enemy.spawn_delay * 1000;
}

void EnemyGenerator::spawnEnemy(GameWorld& world, const EnemyType& enemy)
{
    auto& factory = ObjectFactory::getInstance();
    for (int i = 0; i < enemy.spawn_amount; i++)
    {
        world.addEnemy(factory.createEnemy(enemy.name));
    }
}
