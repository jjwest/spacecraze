#include "../include/asteroid.h"

#include <utility>
#include <random>

#include "../include/asset_manager.h"
#include "../include/constants.h"

using namespace std;

Asteroid::Asteroid(int x, int y) 
    : Enemy(AssetManager::getInstance().getTexture("asteroid"), x, y, 50, 2, 0),
      move_x{0}, move_y{0}
{
    rect.x = x;
    rect.y = y;
    rect.w = texture->getWidth();
    rect.h = texture->getHeight();

    Point exit = calculateExitPoint();
    calculateDirection(exit);
}

void Asteroid::move() 
{   
    rect.x += move_x;
    rect.y += move_y;
    angle++;
}

void Asteroid::update()
{
    move();
    updateAABB();
    killIfOutsideScreen();
}

Point Asteroid::calculateExitPoint() 
{
    random_device rd;
    uniform_int_distribution<int> random_x(50, 1100);
    uniform_int_distribution<int> random_y(30, 700);

    Point exit;
    if (rect.y < 0) 
    {
        exit.x = random_x(rd);
        exit.y = SCREEN_HEIGHT;
    }
    else if (rect.y >= SCREEN_HEIGHT) 
    {
        exit.x = random_x(rd);
        exit.y = 0;
    }
    else if (rect.x <= 0) 
    {
        exit.x = SCREEN_WIDTH;
        exit.y = random_y(rd);
    }
    else if (rect.x >= SCREEN_WIDTH) 
    {
        exit.x = 0;
        exit.y = random_y(rd);
    }

    return exit;
}

void Asteroid::calculateDirection(const Point& exit)
{
    double center_asteroid_x = rect.x + (rect.h / 2);  
    double center_asteroid_y = rect.y + (rect.w / 2);    
    double x_dist = exit.x - center_asteroid_x;
    double y_dist = exit.y - center_asteroid_y;
    double longest = max( abs(x_dist), abs(y_dist) );
    double delta_x = x_dist / longest;
    double delta_y = y_dist / longest;
    move_x = static_cast<int>(round(delta_x * speed));
    move_y = static_cast<int>(round(delta_y * speed));
}

void Asteroid::killIfOutsideScreen()
{
    if (rect.x + (rect.w * 2) < 0 || rect.x > SCREEN_WIDTH || 
        rect.y + (rect.h * 2) < 0 || rect.y > SCREEN_HEIGHT) 
    {
        health = 0;
    }
}

