#include "../include/enemy_generator.h"

#include <random>

#include "../include/constants.h"

using namespace std;

EnemyGenerator::EnemyGenerator()
    :  asteroid_spawn_delay{5}, drone_spawn_delay{3}, blaster_spawn_delay{10}, 
    last_asteroid_spawned{0}, last_drone_spawned{0}, last_blaster_spawned{0}, 
    asteroid_spawn_count{0}, blaster_spawn_count{0}, drone_spawn_count{0} {}

void EnemyGenerator::update(World& world)
{
    current_time = SDL_GetTicks();

    updateAsteroids(world);
    updateDrones(world);
    updateBlasters(world);
}

void EnemyGenerator::updateAsteroids(World& world)
{
    if (current_time - last_asteroid_spawned  > asteroid_spawn_delay * 1000)
    {
        asteroid_spawn_count++;
        world.addAsteroid();
        if (asteroid_spawn_count % 3 == 0)
        {
            world.addAsteroid();
        }
        if (asteroid_spawn_count % 6 == 0)
        {
            asteroid_spawn_delay *= 0.80;
        }
        last_asteroid_spawned = current_time;
    }
}

void EnemyGenerator::updateDrones(World& world)
{
    if (current_time - last_drone_spawned  > drone_spawn_delay * 1000)
    {
        drone_spawn_count++;
        world.addDrone();
        world.addDrone();

        if (drone_spawn_count % 4 == 0)
        {
            world.addDrone();
            world.addDrone();
        }
        else if (drone_spawn_count % 2 == 0)
        {
            world.addDrone();
        }
        if (drone_spawn_count % 5 == 0)
        {
            drone_spawn_delay *= 0.80;
        }

        last_drone_spawned = current_time;
    }
}

void EnemyGenerator::updateBlasters(World& world)
{
    if (current_time - last_blaster_spawned  > blaster_spawn_delay * 1000)
    {
        blaster_spawn_count++;
        world.addBlaster();
        if( blaster_spawn_count % 3 == 0 )
        {
            world.addBlaster();
        }
        if( blaster_spawn_count % 4 == 0 )
        {
            blaster_spawn_delay *= 0.80;
        }

        last_blaster_spawned = current_time;
    }
}

