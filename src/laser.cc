#include "laser.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <math.h>
#include <SDL2/SDL.h>

#include "asset_manager.h"
#include "constants.h"

Laser::Laser(Texture* t, const Point& pos, const Point& destination,
             double dmg, double spd, double ang)
    : GameObject(t, {pos.x - t->getWidth() / 2, pos.y - t->getHeight() / 2}, 1),
      damage{dmg},
      speed{spd},
      current_x{static_cast<double>(pos.x)},
      current_y{static_cast<double>(pos.y)}
{
    // Calculates movement direction
    double center_laser_x = rect.x + (rect.w / 2);  
    double center_laser_y = rect.y + (rect.h / 2);
    
    double x_dist = destination.x - center_laser_x;
    double y_dist = destination.y - center_laser_y;
    
    double longest = std::max( abs(x_dist), abs(y_dist) );

    delta_x = x_dist / longest * speed;
    delta_y = y_dist / longest * speed;

    angle = ang;
}

void Laser::update() 
{
    move();
    updateHitbox(rect);
    killIfOutsideScreen();
}

int Laser::getDamage() const
{
    return damage;
}

void Laser::move()
{
    current_x += delta_x;
    current_y += delta_y;
    rect.x = static_cast<int>( round(current_x) );
    rect.y = static_cast<int>( round(current_y) );
}

void Laser::killIfOutsideScreen()
{
    if ( (rect.x < 0 || rect.x > SCREEN_WIDTH) ||
         (rect.y < 0 || rect.y > SCREEN_HEIGHT) )
    {
        reduceHealth(999);
    }
}

void Laser::setAngle() 
{
     int x, y;
     int center_x, center_y;
     float ang;
     
     SDL_GetMouseState(&x,&y);
     
     center_x = rect.x + (rect.h / 2);
     center_y = rect.y + (rect.w / 2);
     
     ang = atan2(center_y - y, center_x - x);
     ang = ang * 180 / M_PI;
     
     angle = (static_cast<int> (ang) - 90) % 360;
}     
