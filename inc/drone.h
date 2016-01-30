#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include <utility>
#include "moving_object.h"

class Drone: public MovingObject
{
public:
    Drone(Texture* t, int x, int y, int s, int hp);
    ~Drone() = default;
    void move(const std::pair<int, int>& player_pos);
    void update(const std::pair<int, int>& player_pos);
    int getScore() const;
  
private:
    const int score;
};

#endif
