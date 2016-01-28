#include <iostream>
#include <utility>
#include <math.h>
#include <cmath>
#include <algorithm>

#include "../inc/drone.h"

Drone::Drone(Texture* t, int x, int y, 
             int s, int hp, double a,
             std::pair<double, double>* p_pos)
    : Moving_Object(t, x, y, s, hp, a), destination{p_pos}, score{10} {}

void Drone::move()
{
    //Calculates angle to player and moves accordingly
    float angle_to_player;
    double dest_x = destination->first;
    double dest_y = destination->second;
    double center_drone_x = rect.x + (rect.h / 2);  
    double center_drone_y = rect.y + (rect.w / 2);

    double x_dist = dest_x - center_drone_x;
    double y_dist = dest_y - center_drone_y;
    double longest = std::max(abs(x_dist), abs(y_dist));

    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;

    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));

    angle_to_player = atan2(center_drone_y - dest_y, center_drone_x - dest_x);
    angle_to_player = angle_to_player * 180 / M_PI;
    
    angle = (static_cast<int> (angle_to_player)+90)%360;
}

void Drone::update()
{
    move();
    update_AABB();
}

int Drone::get_score() const
{
    return score;
}




