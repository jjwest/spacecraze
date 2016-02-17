#include "../include/player.h"

#include <utility>
#include <SDL2/SDL.h>
#include <string>

#include "../include/asset_manager.h"
#include "../include/constants.h"

using namespace std;

Player::Player(const Point& pos)
    :  GameObject( AssetManager::getInstance().getTexture("player"), pos ), 
       this_aabb{pos.y, pos.x, pos.y + rect.h, pos.x + rect.w},
       has_singularity{true}, health{1}, damage{2}, speed{2}, shoot_cooldown{80},
       last_shot{0} {}

Point Player::getPos() const 
{
    int x = rect.x + rect.h / 2;
    int y = rect.y + rect.w / 2;

    return {x, y};
}

AABB Player::getAABB() const
{
    return this_aabb;
}

void Player::update(LaserManager& lasers)
{
    move();
    shoot(lasers);
    updateAABB();
}

void Player::addSingularity() 
{
    has_singularity = true;
}

void Player::reduceHealth(double dmg)
{
    health -= dmg;
}

void Player::shoot(LaserManager& lasers)
{
    Uint32 current_time = SDL_GetTicks();
    SDL_GetMouseState(NULL, NULL);
    
    if (SDL_BUTTON(SDL_BUTTON_LEFT) && current_time - last_shot > shoot_cooldown) 
    {
        int center_x = rect.x + rect.h / 2;
        int center_y = rect.y + rect.w / 2;
        lasers.addPlayerLaser( {center_x, center_y} );
        last_shot = current_time;
    }
}
void Player::move()
{
    auto state = SDL_GetKeyboardState(NULL);
    
    if (state[SDL_SCANCODE_D])
    {
        rect.x += speed;
    }
    if (state[SDL_SCANCODE_A])
    {
        rect.x -= speed;
    }
    if (state[SDL_SCANCODE_W])
    {
        rect.y -= speed;
    }
    if (state[SDL_SCANCODE_S])
    {
        rect.y += speed;
    }

    setAngle();
}

void Player::setAngle() 
{
     int x, y;
     int center_x, center_y;
     float ang;
     
     SDL_GetMouseState(&x,&y);
     
     center_x = rect.x + (rect.h / 2);
     center_y = rect.y + (rect.w / 2);
     
     ang = atan2(center_y - y, center_x - x);
     ang = ang * 180 / M_PI;
     
     angle = (static_cast<int> (ang) - 90)%360;
}

void Player::updateAABB()
{
    this_aabb = AABB(rect.y + 10, 
                     rect.x + 10, 
                     rect.y + rect.h - 10, 
                     rect.x + rect.w - 10);    
}

