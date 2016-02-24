#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "laser_manager.h"
#include "player.h"
#include "asteroid.h"
#include "blaster.h"
#include "drone.h"
#include "laser.h"
#include "enums.h"

namespace vec
{
    using enemy = std::vector<std::unique_ptr<Enemy>>;
}

class World
{
public:
    World();
    const vec::enemy* getAsteroids() const;
    const vec::enemy* getBlasters() const;
    const vec::enemy* getDrones() const;
    const Player* getPlayer() const;
    void addAsteroid();
    void addBlaster();
    void addDrone();
    void render(SDL_Renderer* renderer);
    void update();

private:
    Player player;
    LaserManager lasers;
    vec::enemy asteroids;
    vec::enemy blasters;
    vec::enemy drones;

    void updateObjects();
};


#endif // _WORLD_H_
