#ifndef LASER_H
#define LASER_H

#include "GameObject.h"
#include "AABB.h"

class Laser : public GameObject
{
public:
    Laser(Texture* t, const Point& origin, const Point& destination,
          float damage, float speed);
    void update();
    int getDamage() const;


private:
    float damage;
    float speed;
    float current_x;
    float current_y;
    float delta_x;
    float delta_y;

    void move();
    void killIfOutsideScreen();
    void setAngle(const Point& destination);
};

#endif
