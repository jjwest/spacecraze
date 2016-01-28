#ifndef ENEMY_GENERATOR
#define ENEMY_GENERATOR

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <random>

#include "world.h"
#include "texture.h"

class EnemyGenerator {
public:
    EnemyGenerator();
    void update(const World&);

private:
    std::vector<std::pair<char, int>> spawn_sections;
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
    void update_asteroids();
    void update_drones();
    void update_blasters();
    std::pair<int, int> getSpawnPoint(Texture*); 
};

#endif
