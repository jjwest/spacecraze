#ifndef BLASTER_H
#define BLASTER_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <random>
#include <iostream>

#include "moving_object.h"
#include "laser.h"

class Blaster: public Moving_Object
{
public:
    Blaster(Texture*, int, int, int, int, double, 
            std::vector<Laser*>* v, Texture* l,
            std::pair<double, double>*);
    ~Blaster() = default;
    void move() override;
    void update() override;
    int get_score() const override; 
  
private:
    std::vector<Laser*>*shots_fired;
    Texture* lasertexture;
    std::pair<double, double>* aim_at; // Sets angle to aim at player position
    std::pair<int, int> go_to; // Sets direction to point on opposite side
    Uint32 last_shot; // Timer for the blasters gun
    const int score;
    void shoot();
    void set_angle();
    void change_direction();
};

#endif
