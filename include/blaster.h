#ifndef BLASTER_H
#define BLASTER_H

#include "enemy.h"

class Blaster: public Enemy
{
public:
    Blaster(const Point &pos);
    void update(const Point& player_pos, LaserManager& lasers) override;
    
private:
    double damage = 1;
    double speed = 1;
    Point move_to{ 0, 0 };
    Uint32 last_shot = 0;
    Uint32 shoot_cooldown = 700;

    void move();
    void shoot(const Point& player_pos, LaserManager& lasers);
    void setAngle(const Point& player_pos);
    void changeDirection();
};

#endif
