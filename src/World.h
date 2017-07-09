#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "Enemy.h"
#include "Enums.h"
#include "Laser.h"
#include "Player.h"
#include "Powerup.h"
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
    void addEnemyLaser(const Point& pos, const Point& dest, float dmg);
    void addPlayerLaser(const Point& pos, float dmg);
    void addPowerup(const Powerup& powerup);
    void clearEnemies();
    void draw(SDL_Renderer* renderer);
    void update();

private:
    WorldState state;
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Laser> enemy_lasers;
    std::vector<Laser> player_lasers;
    std::vector<Powerup> powerups;

    void updateObjects();
    void resolveCollisions();
    void resolvePlayerCollisions();
    void resolveLaserCollisions();
    void resolvePowerups();
    void updateState();
    void removeDeadObjects();
};

#endif // _WORLD_H_
