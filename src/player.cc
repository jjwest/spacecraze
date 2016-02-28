#include "../include/player.h"

#include <utility>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "../include/asset_manager.h"
#include "../include/constants.h"

namespace
{
    SDL_Rect shrinkRect(const SDL_Rect& rect)
    {
        SDL_Rect shrunk_rect = rect;
        shrunk_rect.x -= 5;
        shrunk_rect.y -= 5;
        shrunk_rect.w -= 5;
        shrunk_rect.h -= 5;
        
        return shrunk_rect;
    }
}

Player::Player(const Point& pos)
    :  GameObject( AssetManager::getInstance().getTexture("player"), pos, 1), 
       has_singularity{true}, damage{2}, x_pos{static_cast<double>(rect.x)},
       y_pos{static_cast<double>(rect.y)}, speed{4.5}, shoot_cooldown{80},
       last_shot{0} {}

Point Player::getPos() const 
{
    int x = round(rect.x + rect.h / 2);
    int y = round(rect.y + rect.w / 2);

    return {x, y};
}

void Player::update(LaserManager& laser_manager)
{
    move();
    shoot(laser_manager);
    auto collision_rect = shrinkRect(rect);
    updateAABB(collision_rect);
}

void Player::addSingularity() 
{
    has_singularity = true;
}

void Player::shoot(LaserManager& laser_manager)
{
    auto current_time = SDL_GetTicks();
    SDL_GetMouseState(NULL, NULL);
    
    if (SDL_BUTTON(SDL_BUTTON_LEFT) && current_time - last_shot > shoot_cooldown) 
    {
        int center_x = rect.x + rect.h / 2;
        int center_y = rect.y + rect.w / 2;
        Point current_pos{center_x, center_y};

        laser_manager.addPlayerLaser(current_pos);
        last_shot = current_time;
    }
}
void Player::move()
{
    auto state = SDL_GetKeyboardState(NULL);
    
    if (state[SDL_SCANCODE_D] && rect.x + rect.w + speed <= SCREEN_WIDTH)
    {
        x_pos += speed;
        rect.x = (round(x_pos));
    }
    if (state[SDL_SCANCODE_A] && rect.x - speed >= 0)
    {
        x_pos -= speed;
        rect.x = round(x_pos);
    }
    if (state[SDL_SCANCODE_W] && rect.y - speed >= 0)
    {
        y_pos -= speed;
        rect.y = round(y_pos);
    }
    if (state[SDL_SCANCODE_S] && rect.y + rect.h + speed <= SCREEN_HEIGHT)
    {
        y_pos += speed;
        rect.y = round(y_pos);
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
     
     angle = (static_cast<int> (ang) - 90) % 360;
}
