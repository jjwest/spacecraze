#ifndef ASTEROID_H
#define ASTEROID_H

#include "enemy.h"

class Asteroid: public Enemy
{
public:
    Asteroid(const Point& pos);
    void update(const Point&) override;

private:
    double speed;
    int move_x;
    int move_y;

    Point calculateExitPoint();
    void move();
    void calculateDirection(const Point& exit);
    void killIfOutsideScreen();
};

#endif
