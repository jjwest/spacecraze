#ifndef ENEMY_GENERATOR
#define ENEMY_GENERATOR

#include <SDL2/SDL.h>
#include <vector>

#include "world.h"
#include "texture.h"

class EnemyGenerator
{
public:
    EnemyGenerator();
    void update(World& world);

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

    void updateAsteroids(World& world);
    void updateDrones(World& world);
    void updateBlasters(World& world);
};

#endif
