#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "game_object.h"

class Player: public GameObject
{
public:
    Player(const Point& pos);
    bool hasSpecial() const;
    Point getPos() const;
    void update(World& world);
    void setSpecial(bool state);

private:
    bool has_special = true;
    double damage = 2;
    double speed = 4.5;
    double x_pos;
    double y_pos;
    Uint32 shoot_cooldown = 80;
    Uint32 last_shot = 0;

    bool readyToShoot() const;
    void shoot(World& world);
    void move();
    void useSpecial(World& world);
    void setAngle();
};

#endif
