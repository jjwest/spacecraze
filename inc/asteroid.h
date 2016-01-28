#ifndef ASTEROID_H
#define ASTEROID_H

#include "moving_object.h"

class Asteroid: public Moving_Object
{
public:
    Asteroid(Texture*, int, int, int, int, double);
    void move() override;
    void update() override;

private:
    std::pair<int, int> exit_point;
    int move_x;
    int move_y;
    void calculate_exit_point();
    void calculate_direction();
    void kill_if_outside_screen();
};

#endif
