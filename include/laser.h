#ifndef LASER_H
#define LASER_H

#include "visible_object.h"
#include "aabb.h"

class Laser : public VisibleObject
{
public:
    Laser(Texture* t, const Point& pos, const Point& destination, double dmg);
    AABB getAABB() const;
    void update();
    int getDamage() const;
    
private:
    AABB this_aabb;
    double damage;
    double health;
    double speed;
    double current_x;
    double current_y;
    double delta_x;
    double delta_y;

    void move();
    void updateAABB();
};
#endif
