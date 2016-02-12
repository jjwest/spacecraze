#ifndef _WORLD_H_
#define _WORLD_H_

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

class World
{
public:
    World();
    void addAsteroid();
    void addBlaster();
    void addDrone();
    void update(const std::map<std::string, bool>& player_actions);

private:
    Player player;
    LaserManager lasers;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Blaster>> blasters;
    std::vector<std::unique_ptr<Drone>> drones;

    void updateObjects(const std::map<std::string, bool>& player_actions);
    void handleCollisions();
};


#endif // _WORLD_H_
