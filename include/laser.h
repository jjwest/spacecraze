#ifndef LASER_H
#define LASER_H

#include "game_object.h"
#include "aabb.h"

class Laser : public GameObject
{
public:
    Laser(Texture* t, const Point& pos, const Point& destination,
          double dmg, double sp);
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
