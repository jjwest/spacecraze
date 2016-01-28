#include "../inc/laser.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>


Laser::Laser(Texture* t, int x, int y, int s,
             int hp, int dmg, std::pair<int, int> aim_at):
    Moving_Object(t, x, y, s, hp), damage{dmg}                                        
{
    // Calculates movement direction
    double center_laser_x = rect.x + (rect.h / 2);  
    double center_laser_y = rect.y + (rect.w / 2);

    double x_dist = aim_at.first - center_laser_x;
    double y_dist = aim_at.second - center_laser_y;
    
    double longest = std::max(abs(x_dist), abs(y_dist));

    delta_x = x_dist / longest;
    delta_y = y_dist / longest;
}

void Laser::move()
{
    double x_move = delta_x * speed;
    double y_move = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(x_move));
    rect.y = rect.y + static_cast<int>(round(y_move));
}

void Laser::update() 
{
    move();
    update_AABB();

    // Kills laser if outside screen
    if( (rect.x < 0 || rect.x > 1024) || (rect.y < 0 || rect.y > 768) )
    {
        current_hp = 0;
    }
}

int Laser::get_damage() const
{
  return damage;
}

