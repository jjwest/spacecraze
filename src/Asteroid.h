#ifndef ASTEROID_H
#define ASTEROID_H

#include "Enemy.h"

class Asteroid: public Enemy
{
public:
    Asteroid(const SDL_Rect& rect);
    void update(const Point&, World&) override;

private:
    float speed = 1.5;
    int move_x = 0;
    int move_y = 0;

    Point calculateExitPoint();
    void calculateDirection(const Point& destination);
    void move();
    void killIfOutsideScreen();
};

#endif
