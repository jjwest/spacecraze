#ifndef LASER_H
#define LASER_H

#include "moving_object.h"

class Laser : public Moving_Object
{
public:
    Laser(Texture*, int, int, int, int, double, int, std::pair<int, int>);
    ~Laser() = default;
    void move() override;
    void update();
    int get_damage() const;
    
private:
  int damage;
  double delta_x;
  double delta_y;
};
#endif
