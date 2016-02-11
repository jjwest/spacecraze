#ifndef PLAYER_H
#define PLAYER_H

#include "visible_object.h"

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <memory>

#include "texture.h"
#include "aabb.h"

class Player: public VisibleObject
{
public:
    Player(const Point& pos);
    Point getPos() const;
    AABB getAABB() const;
    void update(const std::map<std::string, bool>& player_actions);
    void addSingularity();
    void reduceHealth(double dmg);

private:
    AABB this_aabb;
    bool singularity;
    double health;
    double damage;
    int speed;
    Uint32 shoot_cooldown;
    Uint32 last_shot;

    void shoot();
    void move(const std::map<std::string, bool>& player_actions);
    void setAngle();
    void updateAABB();
};

#endif
