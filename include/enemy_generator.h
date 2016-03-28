#ifndef ENEMY_GENERATOR
#define ENEMY_GENERATOR

#include <vector>
#include <string>
#include <memory>

#include "world.h"
#include "object_factory.h"


class EnemyGenerator
{
public:
    EnemyGenerator();
    void update(World& world);

private:
struct EnemyType
{
    std::string name;
    double spawn_delay;
    int spawn_amount;
    int spawn_multiplier;
    int spawns_until_decreased_delay;
    int num_times_spawned = 0;
    Uint32 last_time_spawned = SDL_GetTicks();
};
        
    std::vector<EnemyType> enemy_types;

    bool readyToSpawn(const EnemyType& enemy, Uint32 current_time);
    void spawnEnemy(World& world, const EnemyType& enemy);
};

#endif
