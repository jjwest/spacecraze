#ifndef LASER_H
#define LASER_H

#include "GameObject.h"
#include "AABB.h"

class Laser : public GameObject
{
public:
    Laser(Texture* t, const Point& origin, const Point& destination,
          double damage, double speed);
    void update();
    int getDamage() const;


private:
    double damage;
    double speed;
    double current_x;
    double current_y;
    double delta_x;
    double delta_y;

    void move();
    void killIfOutsideScreen();
    void setAngle();
};

#endif
