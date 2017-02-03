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

void Asteroid::move()
{
    hitbox.x += move_x;
    hitbox.y += move_y;
    angle++;
}


void Asteroid::calculateDirection(const Point& exit)
{
    double center_asteroid_x = hitbox.x + (hitbox.h / 2);
    double center_asteroid_y = hitbox.y + (hitbox.w / 2);
    double x_dist = exit.x - center_asteroid_x;
    double y_dist = exit.y - center_asteroid_y;
    double longest = std::max( abs(x_dist), abs(y_dist) );
    double delta_x = x_dist / longest;
    double delta_y = y_dist / longest;
    move_x = int( round(delta_x * speed) );
    move_y = int( round(delta_y * speed) );
}

void Asteroid::killIfOutsideScreen()
{
    if (hitbox.x + (hitbox.w * 2) < 0 || hitbox.x > SCREEN_WIDTH ||
        hitbox.y + (hitbox.h * 2) < 0 || hitbox.y > SCREEN_HEIGHT)
    {
        reduceHealth(500);
    }
}
