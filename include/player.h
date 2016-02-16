#ifndef PLAYER_H
#define PLAYER_H

#include "visible_object.h"

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <memory>

#include "laser_manager.h"
#include "texture.h"
#include "aabb.h"

class Player: public VisibleObject
{
public:
    Player(const Point& pos);
    Point getPos() const;
    AABB getAABB() const;
    void update(LaserManager& lasers);
    void addSingularity();
    void reduceHealth(double dmg);

private:
    AABB this_aabb;
    bool has_singularity;
    double health;
    double damage;
    int speed;
    Uint32 shoot_cooldown;
    Uint32 last_shot;

    void shoot(LaserManager& lasers);
    void move();
    void setAngle();
    void updateAABB();
};

#endif
