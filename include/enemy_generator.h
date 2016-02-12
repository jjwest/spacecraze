#ifndef ENEMY_GENERATOR
#define ENEMY_GENERATOR

#include <SDL2/SDL.h>
#include <vector>

#include "enemy_manager.h"
#include "texture.h"

class EnemyGenerator
{
public:
    EnemyGenerator();
    void update(EnemyManager& enemies);

private:
    double asteroid_spawn_delay;
    double drone_spawn_delay;
    double blaster_spawn_delay;
    Uint32 current_time;
    Uint32 last_asteroid_spawned; 
    Uint32 last_drone_spawned;
    Uint32 last_blaster_spawned;
    int asteroid_spawn_count;
    int blaster_spawn_count;
    int drone_spawn_count;

    void updateAsteroids(EnemyManager& enemies);
    void updateDrones(EnemyManager& enemies);
    void updateBlasters(EnemyManager& enemies);
};

#endif
