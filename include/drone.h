#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include "enemy.h"

class Drone: public Enemy
{
public:
    Drone(const Point& pos);
    void update(const Point& player_pos, LaserManager&) override;
  
private:
    double speed = 2;
    
    void move(const Point& player_pos);
};

#endif
