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

class World
{
public:
    World();
    bool playerIsDead() const;
    void addEnemy(std::unique_ptr<Enemy> enemy);
    void addEnemyLaser(const Point& pos, const Point& dest, double dmg);
    void addPlayerLaser(const Point& pos, double dmg);
    void killAllEnemies();
    void update(ScoreKeeper& score);
    void draw(SDL_Renderer* renderer);

private:
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Laser>> enemy_lasers;
    std::vector<std::unique_ptr<Laser>> player_lasers;

    void updateScore(ScoreKeeper& s);
    void updateObjects();
    void resolveCollisions();
    void resolveLaserCollisions();
    void resolvePlayerCollisions();
    void removeDeadObjects();
};

#endif // _WORLD_H_
