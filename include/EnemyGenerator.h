#ifndef ENEMY_GENERATOR
#define ENEMY_GENERATOR

#include <vector>
#include <string>

#include "World.h"

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
    int spawns_until_increased_spawn_rate;
    int times_spawned = 0;
    Uint32 last_time_spawned = SDL_GetTicks();
};

    std::vector<EnemyType> enemy_types;

    bool readyToSpawn(const EnemyType& enemy);
    void spawnEnemy(World& world, const EnemyType& enemy);
    void updateEnemyType(EnemyType& enemy);
    std::unique_ptr<Enemy> createEnemy(const std::string& type);
};

#endif
