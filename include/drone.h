#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include "enemy.h"

class Drone: public Enemy
{
public:
    Drone(const Point& pos);
    void update(const Point& player_pos) override;
    int getScore() const;
  
private:
    double speed;
    
    void move(const Point& player_pos);
};

#endif
