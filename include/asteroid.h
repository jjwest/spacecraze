#ifndef ASTEROID_H
#define ASTEROID_H

#include "enemy.h"

class Asteroid: public Enemy
{
public:
    Asteroid(int x, int y);
    void update();

private:
    int move_x;
    int move_y;

    void move();
    Point calculateExitPoint();
    void calculateDirection(const Point& exit);
    void killIfOutsideScreen();
};

#endif
