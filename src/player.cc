#include "../include/player.h"

#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../include/asset_manager.h"
#include "../include/constants.h"

using namespace std;

Player::Player(int x, int y)
    :  VisibleObject( AssetManager::getInstance().getTexture("player") ), 
       this_aabb{1, 1, 1, 1}, singularity{true}, health{1}, damage{2}, speed{2}, 
       shoot_cooldown{80}, last_shot{0}
{    
    rect.x = x;
    rect.y = y;
    rect.w = texture->getWidth();
    rect.h = texture->getHeight();

    this_aabb = AABB(y, x, y + rect.h, x + rect.w);
}

void Player::shoot()
{
    // Uint32 current_time{ SDL_GetTicks() };
    // if (current_time - last_shot > shoot_cooldown) 
    // {
    //     int mouse_x, mouse_y;
    //     SDL_GetMouseState(&mouse_x, &mouse_y);
    //     pair<int, int> direction{mouse_x, mouse_y};

    //     last_shot = current_time;
    // }
}
void Player::move(const map<string, bool>& player_actions)  
{    
    if (player_actions.at("RIGHT") && rect.x + rect.w + speed < SCREEN_WIDTH) 
    {
        rect.x += speed;
    }
    if (player_actions.at("LEFT") && rect.x > 0 + speed) 
    {
        rect.x -= speed;
    }
    if (player_actions.at("UP") && rect.y > 0 + speed) 
    {
        rect.y -= speed;
    }
    if (player_actions.at("DOWN") && rect.y < SCREEN_HEIGHT - speed + rect.h) 
    {
        rect.y += speed;
    }

    setAngle();
}

void Player::update(const map<string, bool>& player_actions)
{
    move(player_actions);
    updateAABB();
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

void Player::addSingularity() 
{
    singularity = true;
}

pair<int, int> Player::getPos() const 
{
    int pos_x {rect.x + rect.h / 2};
    int pos_y {rect.y + rect.w / 2};
    pair<int, int> player_pos{pos_x, pos_y};

    return player_pos;
}
               
void Player::updateAABB()
{
    this_aabb = AABB(rect.y + 10, 
                     rect.x + 10, 
                     rect.y + rect.h - 10, 
                     rect.x + rect.w - 10);    
}
