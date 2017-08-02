#include "Laser.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <math.h>
#include <SDL2/SDL.h>

#include "AssetManager.h"
#include "Constants.h"

Laser::Laser(Texture* t, const Point& origin, const Point& destination,
             float damage, float speed)
    : GameObject(t, {origin.x - t->getWidth() / 2,
		origin.y - (t->getHeight() / 2) - 10,
		t->getWidth() / 2,
		t->getHeight() / 2}, 1),
      damage{damage},
      speed{speed},
      current_x{static_cast<float>(origin.x)},
      current_y{static_cast<float>(origin.y)}
{
    float center_x = hitbox.x + (hitbox.w / 2);
    float center_y = hitbox.y + (hitbox.h / 2);

    { // Calculate movement direction
	float x_distance = destination.x - center_x;
	float y_distance = destination.y - center_y;
	float longest = std::max( std::abs(x_distance), std::abs(y_distance) );

	delta_x = x_distance / longest;
	delta_y = y_distance / longest;
    }
    { // Calculate angle
	float angle_in_radians = atan2(center_y - destination.y, center_x - destination.x);
	float angle_in_degrees = angle_in_radians * 180 / M_PI;

	angle = (static_cast<int>(angle_in_degrees) - 90) % 360;
    }
}

void Laser::update()
{
    current_x += delta_x * speed;
    current_y += delta_y * speed;
    hitbox.x = static_cast<int>( round(current_x) );
    hitbox.y = static_cast<int>( round(current_y) );

    bool outside_screen = (hitbox.x + hitbox.w < 0 || hitbox.x > SCREEN_WIDTH ||
			   hitbox.y + hitbox.h < 0 || hitbox.y > SCREEN_HEIGHT);

    if (outside_screen) kill();

    updateHitbox(hitbox);
}

int Laser::getDamage() const
{
    return damage;
}
