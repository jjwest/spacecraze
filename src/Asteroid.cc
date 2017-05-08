#include "Asteroid.h"

#include <utility>
#include <random>

#include "AssetManager.h"
#include "Constants.h"

Asteroid::Asteroid(const SDL_Rect& rect)
    : Enemy(AssetManager::getInstance().getTexture("asteroid"), rect, 50, 0)
{
    Point exit = calculateExitPoint();
    calculateDirection(exit);
}

void Asteroid::update(const Point&, World&)
{
    move();
    updateHitbox(hitbox);
    killIfOutsideScreen();
}

Point Asteroid::calculateExitPoint()
{
    std::random_device rd;
    std::uniform_int_distribution<int> random_x(50, 1100);
    std::uniform_int_distribution<int> random_y(30, 700);

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

    return exit;
}

void Asteroid::calculateDirection(const Point& destination)
{
    int asteroid_center_x = hitbox.x + (hitbox.w / 2);
    int asteroid_center_y = hitbox.y + (hitbox.h / 2);

    int x_dist = destination.x - asteroid_center_x;
    int y_dist = destination.y - asteroid_center_y;

    int longest = std::max( abs(x_dist), abs(y_dist) );

    int delta_x = x_dist / longest;
    int delta_y = y_dist / longest;
    move_x = round(delta_x * speed);
    move_y = round(delta_y * speed);
}


void Asteroid::move()
{
    hitbox.x += move_x;
    hitbox.y += move_y;
    ++angle;
}


void Asteroid::killIfOutsideScreen()
{
    if (hitbox.x + hitbox.w < 0 || hitbox.x > SCREEN_WIDTH ||
        hitbox.y + hitbox.h < 0 || hitbox.y > SCREEN_HEIGHT)
    {
        kill();
    }
}
