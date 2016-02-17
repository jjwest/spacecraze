#include "../include/laser.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <math.h>
#include <SDL2/SDL.h>

#include "../include/asset_manager.h"
#include "../include/constants.h"

Laser::Laser(Texture* t, const Point& pos, const Point& destination, double dmg)
    : GameObject(t, pos),
      this_aabb{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w},
      damage{dmg}, health{1}, speed{3}, current_x{pos.x}, current_y{pos.y}
{
    // Calculates movement direction
    double center_laser_x = rect.x + (rect.h / 2);  
    double center_laser_y = rect.y + (rect.w / 2);
    
    double x_dist = destination.x - center_laser_x;
    double y_dist = destination.y - center_laser_y;
    
    double longest = std::max( abs(x_dist), abs(y_dist) );

    delta_x = x_dist / longest;
    delta_y = y_dist / longest;
}

AABB Laser::getAABB() const
{
    return this_aabb;
}

void Laser::update() 
{
    move();
    updateAABB();

    // Kills laser if outside screen
    if ( (rect.x < 0 || rect.x > SCREEN_WIDTH) ||
         (rect.y < 0 || rect.y > SCREEN_HEIGHT) )
    {
        health = 0;
    }
}

int Laser::getDamage() const
{
    return damage;
}

void Laser::move()
{
    current_x += delta_x;
    current_y += delta_y;
    rect.x += static_cast<int>( round(current_x) );
    rect.y += static_cast<int>( round(current_y) );
}

void Laser::updateAABB()
{
    this_aabb = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}
