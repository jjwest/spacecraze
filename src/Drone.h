#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include "Enemy.h"

class Drone: public Enemy
{
public:
    Drone(const SDL_Rect& rect);
    void update(const Point& player_pos, World&) override;

private:
    float speed = 2;

    void move(const Point& player_pos);
};

#endif
