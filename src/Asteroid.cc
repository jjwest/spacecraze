#include "Asteroid.h"

#include <random>
#include <utility>

#include "AssetManager.h"
#include "Constants.h"

Asteroid::Asteroid(const SDL_Rect& rect)
    : Enemy(AssetManager::instance().getTexture("asteroid"), rect, 50, 0)
{
    std::random_device rd;
    std::uniform_int_distribution<int> random_x(50, 1100);
    std::uniform_int_distribution<int> random_y(30, 700);

    // Calculate the exit point
    Point exit;
    if (hitbox.y < 0)
    {
        exit.x = random_x(rd);
        exit.y = SCREEN_HEIGHT;
    }
    else if (hitbox.y >= SCREEN_HEIGHT)
    {
        exit.x = random_x(rd);
        exit.y = 0;
    }
    else if (hitbox.x <= 0)
    {
        exit.x = SCREEN_WIDTH;
        exit.y = random_y(rd);
    }
    else if (hitbox.x >= SCREEN_WIDTH)
    {
        exit.x = 0;
        exit.y = random_y(rd);
    }

    // Calculate the movement delta
    int asteroid_center_x = hitbox.x + (hitbox.w / 2);
    int asteroid_center_y = hitbox.y + (hitbox.h / 2);

    int x_distance = exit.x - asteroid_center_x;
    int y_distance = exit.y - asteroid_center_y;

    int longest = std::max( abs(x_distance), abs(y_distance) );

    int delta_x = x_distance / longest;
    int delta_y = y_distance / longest;

    move_x = round(delta_x * speed);
    move_y = round(delta_y * speed);
}

void Asteroid::update(const Point&, World&)
{
    hitbox.x += move_x;
    hitbox.y += move_y;
    ++angle;

    bool outside_screen = (hitbox.x + hitbox.w < 0 ||
						   hitbox.y + hitbox.h < 0 ||
						   hitbox.x > SCREEN_WIDTH ||
						   hitbox.y > SCREEN_HEIGHT);
    if (outside_screen)
    {
        kill();
    }

    updateHitbox(hitbox);
}
