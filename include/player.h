#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <memory>

#include "laser_manager.h"
#include "texture.h"
#include "aabb.h"

class Player: public GameObject
{
public:
    Player(const Point& pos);
    Point getPos() const;
    void update(LaserManager& laser_manager);
    void addSingularity();

private:
    bool has_singularity;
    double damage;
    double x_pos;
    double y_pos;
    double speed;
    Uint32 shoot_cooldown;
    Uint32 last_shot;

    bool readyToShoot() const;
    void shoot(LaserManager& laser_manager);
    void move();
    void setAngle();
};

#endif
