#include "../include/enemy_generator.h"

#include <random>

#include "../include/constants.h"

using namespace std;

EnemyGenerator::EnemyGenerator()
    :  asteroid_spawn_delay{5}, drone_spawn_delay{3}, blaster_spawn_delay{10}, 
    last_asteroid_spawned{0}, last_drone_spawned{0}, last_blaster_spawned{0}, 
    asteroid_spawn_count{0}, blaster_spawn_count{0}, drone_spawn_count{0} {}

void EnemyGenerator::update()
{
    // current_time = SDL_GetTicks();

    // updateAsteroid();
    // update_drone();
    // update_blaster();
}

void EnemyGenerator::updateAsteroids()
{
    // if (current_time - last_asteroid_spawned  > asteroid_spawn_delay * 1000)
    // {
    //     asteroid_spawn_count++;

    //     if (asteroid_spawn_count % 3 == 0)
    //     {
    //         world.addEnemyAsteroid();
    //     }
    //     if (asteroid_spawn_count % 6 == 0)
    //     {
    //         asteroid_spawn_delay *= 0.80;
    //     }       
    // }
}

void EnemyGenerator::updateDrones()
{
//     if (current_time - last_drone_spawned)  > drone_spawn_delay * 1000)
// {
//         world.addEnemyDrone();
//         world.addEnemyDrone();
//         drone_spawn_count++;

//         if (drone_spawn_count % 4 == 0) {
//             generate_drone();
//             generate_drone();
//         }
//         else if (drone_spawn_count % 2 == 0) {
//             generate_drone();
//         }
//         if (drone_spawn_count % 5 == 0) {
//             drone_spawn_delay *= 0.80;
//         }
//     }
}

void EnemyGenerator::updateBlasters()
{
    // if( (current_time - last_blaster_spawned)  > (blaster_spawn_delay * 1000))
    // {
    //     generate_blaster();
    //     blaster_spawn_count++;
    //     if( blaster_spawn_count % 3 == 0 )
    //     {
    //         generate_blaster();
    //     }
    //     if( blaster_spawn_count % 4 == 0 )
    //     {
    //         blaster_spawn_delay *= 0.80;
    //     }
    // }
}

