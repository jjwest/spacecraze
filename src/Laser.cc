#include "Laser.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <math.h>
#include <SDL2/SDL.h>

#include "AssetManager.h"
#include "Constants.h"

Laser::Laser(Texture* t, const Point& origin, const Point& destination,
             double damage, double speed)
    : GameObject(t, {origin.x - t->getWidth() / 2,
		origin.y - (t->getHeight() / 2) - 10,
		t->getWidth() / 2,
		t->getHeight() / 2}, 1),
      damage{damage},
      speed{speed},
      current_x{static_cast<double>(origin.x)},
      current_y{static_cast<double>(origin.y)}
{
    // Calculates movement direction
    double center_laser_x = hitbox.x + (hitbox.w / 2);
    double center_laser_y = hitbox.y + (hitbox.h / 2);
    double x_dist = destination.x - center_laser_x;
    double y_dist = destination.y - center_laser_y;
    double longest = std::max( std::abs(x_dist), std::abs(y_dist) );

    delta_x = x_dist / longest;
    delta_y = y_dist / longest;

    setAngle(destination);
}

void Laser::update()
{
    move();
    updateHitbox(hitbox);
    killIfOutsideScreen();
}

int Laser::getDamage() const
{
    return damage;
}

void Laser::move()
{
    current_x += delta_x * speed;
    current_y += delta_y * speed;
    hitbox.x = static_cast<int>( round(current_x) );
    hitbox.y = static_cast<int>( round(current_y) );
}

void Laser::killIfOutsideScreen()
{
    if ( hitbox.x + hitbox.w < 0 || hitbox.x > constants::SCREEN_WIDTH ||
         hitbox.y + hitbox.h < 0 || hitbox.y > constants::SCREEN_HEIGHT )
    {
        kill();
    }
}

void Laser::setAngle(const Point& destination)
{
     double center_x = hitbox.x + (hitbox.w / 2);
     double center_y = hitbox.y + (hitbox.h / 2);
     double angle_in_radians = atan2(center_y - destination.y, center_x - destination.x);
     double angle_in_degrees = angle_in_radians * 180 / M_PI;

     angle = (static_cast<int>(angle_in_degrees) - 90) % 360;
}