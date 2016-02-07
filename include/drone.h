#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include "enemy.h"

class Drone: public Enemy
{
public:
    Drone(int x, int y);
    void update(const Point& player_pos);
    int getScore() const;
  
private:    
    void move(const Point& player_pos);
};

#endif
