#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "laser.h"
#include "user_interface.h"
#include "enums.h"
#include "score_keeper.h"

struct WorldState
{
    bool player_dead = false;
    bool player_has_special = true;
    int score = 0;
};

class World
{
public:
    World();
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void addEnemyLaser(const Point& pos, const Point& dest, double dmg);
    void addPlayerLaser(const Point& pos, double dmg);
    void killAllEnemies();
    void draw(SDL_Renderer* renderer);
    void update();
    WorldState getState() const;

private:
    WorldState state;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;

    void updateScore();
    void updateObjects();
    void resolveCollisions();
    void resolveLaserCollisions();
    void resolvePlayerCollisions();
    void removeDeadObjects();
    void updateState();
};

#endif // _WORLD_H_
