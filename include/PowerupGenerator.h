#ifndef _POWERUPGENERATOR_H_
#define _POWERUPGENERATOR_H_

#include "World.h"

#include <random>
#include <string>
#include <vector>

class PowerupGenerator
{
public:
    PowerupGenerator() = default;
    void update(World& world);

private:
    std::random_device random;
    std::vector<std::string> powerups{"doubledamage"};

    const Uint32 spawn_delay_ms = 10000;
    Uint32 last_spawn_time = SDL_GetTicks();

    void spawnPowerup(World& world);
    Point getSpawnPoint();
};


#endif // _POWERUPGENERATOR_H_
