#ifndef ASTEROID_H
#define ASTEROID_H

#include "enemy.h"

class Asteroid: public Enemy
{
public:
    Asteroid(const Point& pos);
    void update(const Point&, LaserManager&) override;

private:
    double speed = 1.5;
    int move_x = 0;
    int move_y = 0;

    Point calculateExitPoint();
    void move();
    void calculateDirection(const Point& exit);
    void killIfOutsideScreen();
};

#endif
