#ifndef ASTEROID_H
#define ASTEROID_H

#include "moving_object.h"

class Asteroid: public MovingObject
{
public:
    Asteroid(Texture*, int, int, int, int);
    void move();
    void update();

private:
    std::pair<int, int> exit_point;
    int move_x;
    int move_y;
    void calculateExitPoint();
    void calculateDirection();
    void killIfOutsideScreen();
};

#endif
