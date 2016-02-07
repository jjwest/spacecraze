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
    Blaster(int x, int y);
    void update();
  
private:
    Point move_to; // Sets direction to point on opposite side
    Uint32 last_shot; // Timer for the blasters gun

    void move();
    void shoot();
    void setAngle();
    void changeDirection();
};

#endif
