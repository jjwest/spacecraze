#include "../inc/enemy_generator.h"
#include "../inc/globals.h"

using namespace std;

Enemy_Generator::Enemy_Generator()
    :  asteroid_spawn_delay{5}, drone_spawn_delay{3}, blaster_spawn_delay{10}, 
    last_asteroid_spawned{0}, last_drone_spawned{0}, last_blaster_spawned{0}, 
    asteroid_spawn_count{0}, blaster_spawn_count{0}, drone_spawn_count{0} {

    spawn_sections.push_back({'T', SCREEN_WIDTH});
    spawn_sections.push_back({'L', SCREEN_HEIGHT});
    spawn_sections.push_back({'D', SCREEN_WIDTH});
    spawn_sections.push_back({'R', SCREEN_HEIGHT});
}

void Enemy_Generator::update(const World& world) {
    current_time = SDL_GetTicks();

    update_asteroid(world);
    update_drone(world);
    update_blaster(world);
}

void Enemy_Generator::update_asteroids(const World& world) {
    if ( current_time - last_asteroid_spawned  > asteroid_spawn_delay * 1000 ) {
        world.addEnemyAsteroid();
        asteroid_spawn_count++;

        if ( asteroid_spawn_count % 3 == 0 ) {
            world.addEnemyAsteroid();
        }
        if ( asteroid_spawn_count % 6 == 0 ) {
            asteroid_spawn_delay *= 0.80;
        }       
    }
}

void Enemy_Generator::update_drone(const World& world) {
    if (current_time - last_drone_spawned)  > drone_spawn_delay * 1000) {
        world.addEnemyDrone();
        world.addEnemyDrone();
        drone_spawn_count++;

        if (drone_spawn_count % 4 == 0) {
            generate_drone();
            generate_drone();
        }
        else if (drone_spawn_count % 2 == 0) {
            generate_drone();
        }
        if (drone_spawn_count % 5 == 0) {
            drone_spawn_delay *= 0.80;
        }
    }
}

void Enemy_Generator::update_blaster()
{
    if( (current_time - last_blaster_spawned)  > (blaster_spawn_delay * 1000))
    {
        generate_blaster();
        blaster_spawn_count++;
        if( blaster_spawn_count % 3 == 0 )
        {
            generate_blaster();
        }
        if( blaster_spawn_count % 4 == 0 )
        {
            blaster_spawn_delay *= 0.80;
        }
    }
}

pair<int, int> Enemy_Generator::getSpawnPoint(Texture* texture)
{
    uniform_int_distribution<int> index(0,3);
    random_device rd;
    
    pair<char, int> section{ spawn_sections.at(index(rd)) };
    pair<int, int> spawn_point;

    uniform_int_distribution<int> dist(0, section.second);

    switch( section.first  )
    {
    case 'T':
        spawn_point = {dist(rd), 0 - texture->get_height()};
        break;
    case 'L':
        spawn_point = {0 - texture->get_width(), dist(rd)};
        break;
        
    case 'B':
        spawn_point = {dist(rd), SCREEN_HEIGHT};
        break;

    case 'R':
        spawn_point = {SCREEN_WIDTH, dist(rd)};
        break;
    }

    return spawn_point;
}
