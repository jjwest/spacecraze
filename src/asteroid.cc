#include "../inc/asteroid.h"
#include "../inc/globals.h"

#include <utility>
#include <random>

using namespace std;

Asteroid::Asteroid(Texture* t, int x, int y, int s, int hp) 
: MovingObject(t, x, y, s, hp)
{
    calculateExitPoint();
    calculateDirection();
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

void Asteroid::calculateExitPoint() 
{
    random_device rd;
    uniform_int_distribution<int> random_x(50, 1100);
    uniform_int_distribution<int> random_y(30, 700);

    if (rect.y < 0) {
        exit_point.first = random_x(rd);
        exit_point.second = SCREEN_HEIGHT;
    }
    else if (rect.y >= SCREEN_HEIGHT) {
        exit_point.first = random_x(rd);
        exit_point.second = 0;
    }
    else if (rect.x <= 0) {
        exit_point.first = SCREEN_WIDTH;
        exit_point.second = random_y(rd);
    }
    else if (rect.x >= SCREEN_WIDTH) {
        exit_point.first = 0;
        exit_point.second = random_y(rd);
    }
}

void Asteroid::calculateDirection()
{
    double center_asteroid_x = rect.x + (rect.h / 2);  
    double center_asteroid_y = rect.y + (rect.w / 2);    
    double x_dist = exit_point.first - center_asteroid_x;
    double y_dist = exit_point.second - center_asteroid_y;
    double longest = max(abs(x_dist), abs(y_dist));    
    double delta_x = x_dist / longest;
    double delta_y = y_dist / longest;
    move_x = static_cast<int>(round(delta_x * speed));
    move_y = static_cast<int>(round(delta_y * speed));
}

void Asteroid::killIfOutsideScreen()
{
    if (rect.x + (rect.w * 2) < 0 || rect.x > SCREEN_WIDTH || 
        rect.y + (rect.h * 2) < 0 || rect.y > SCREEN_HEIGHT) {
        current_hp = 0;
    }
}

