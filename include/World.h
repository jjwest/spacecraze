#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "Enemy.h"
#include "Enums.h"
#include "Laser.h"
#include "Player.h"
#include "ScoreKeeper.h"
#include "UserInterface.h"

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
    WorldState getState() const;
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void addEnemyLaser(const Point& pos, const Point& dest, double dmg);
    void addPlayerLaser(const Point& pos, double dmg);
    void draw(SDL_Renderer* renderer);
    void killAllEnemies();
    void update();

private:
    WorldState state;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;

    void updateObjects();
    void resolveCollisions();
    void resolvePlayerCollisions();
    void resolveLaserCollisions();
    void updateState();
    void removeDeadObjects();
};

#endif // _WORLD_H_
