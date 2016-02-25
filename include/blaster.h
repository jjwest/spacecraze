#ifndef BLASTER_H
#define BLASTER_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <random>

#include "enemy.h"

class Blaster: public Enemy
{
public:
    Blaster(const Point& pos);
    void update(const Point& player_pos) override;
  
private:
    double damage;
    double speed;
    Point move_to;    
    Uint32 last_shot;
    Uint32 shoot_cooldown;

    void move();
    void shoot(const Point& player_pos);
    void setAngle(const Point& player_pos);
    void changeDirection();
};

#endif
