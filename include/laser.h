#ifndef LASER_H
#define LASER_H

#include "game_object.h"
#include "aabb.h"

class Laser : public GameObject
{
public:
    Laser(Texture* t, const Point& pos, const Point& destination,
          double dmg, double spd, double angl);
    void update();
    int getDamage() const;
    
private:
    double damage;
    double speed;
    double current_x;
    double current_y;
    double delta_x = 0;
    double delta_y = 0;

    void move();
    void killIfOutsideScreen();
    void setAngle();
};

#endif
