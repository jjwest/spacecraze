#ifndef LASER_H
#define LASER_H

#include "moving_object.h"

class Laser : public MovingObject
{
public:
    Laser(Texture*, int, int, int, int, int, std::pair<int, int>);
    ~Laser() = default;
    void move();
    void update();
    int get_damage() const;
    
private:
  int damage;
  double delta_x;
  double delta_y;
};
#endif
