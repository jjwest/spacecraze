#ifndef DRONE_H
#define DRONE_H

#include <utility>
#include <utility>
#include "moving_object.h"

class Drone: public Moving_Object
{
public:
    Drone(Texture*, int, int, int, int, double,
          std::pair<double, double>*);
    ~Drone() = default;
    void move() override;
    void update() override;
    int get_score() const;
  
private:
    std::pair<double, double>* destination; // Destination is always the playerships position
    const int score;
};

#endif
