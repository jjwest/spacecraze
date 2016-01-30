#ifndef BLASTER_H
#define BLASTER_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <random>
#include <iostream>

#include "moving_object.h"
#include "laser.h"
#include "world.h"

class Blaster: public MovingObject
{
public:
    Blaster(Texture* t, int x, int y, int s, int hp);
    ~Blaster() = default;
    void move();
    void update(World& world);
    int getScore() const override; 
  
private:
    std::pair<int, int> go_to; // Sets direction to point on opposite side
    Uint32 last_shot; // Timer for the blasters gun
    int score;
    void shoot(World& world);
    void setAngle();
    void changeDirection();
};

#endif
