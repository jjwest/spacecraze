#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <map>

#include "asteroid.h"
#include "blaster.h"
#include "drone.h"
#include "player.h"
#include "laser.h"
#include "enums.h"

class World 
{
public:
    World();
    ~World();
    GameStates update(SDL_Renderer*, const std::map<std::string, bool>&);
    void addEnemyAsteroid();
    void addEnemyBlaster();
    void addEnemyDrone();
    void addEnemyLaser(const std::pair<int, int>& from);
    void addPlayerLaser(int x, int y, int dmg, 
                        const std::pair<int, int>& direction);

private:
    Player player;              
    SDL_Texture* background;
    std::vector<Asteroid*> asteroids;
    std::vector<Blaster*> blasters;
    std::vector<Drone*> drones;
    std::vector<Laser*> friendly_lasers;
    std::vector<Laser*> hostile_lasers;
    
    GameStates handleCollisions();
    void draw(SDL_Renderer*);
};


#endif // _WORLD_H_
