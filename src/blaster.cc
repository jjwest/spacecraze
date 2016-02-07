#include "../include/blaster.h"
#include "../include/constants.h"
#include "../include/asset_manager.h"

using namespace std;

Blaster::Blaster(int x, int y)
    : Enemy(AssetManager::getInstance().getTexture("blaster"), x, y, 15, 1, 40),
      last_shot{0} {}


void Blaster::shoot()
{
    // Uint32 current_time = SDL_GetTicks();

    // if (current_time - last_shot > 300) {
    //     // pair<int, int> aim_to;
    //     // aim_to.first = static_cast<int> (player_pos.first);
    //     // aim_to.second = static_cast<int> (player_pos.second);
    //     // setAngle();
    //     pair<int, int> this_pos{rect.x, rect.y};
    //     world.addEnemyLaser(this_pos);
    //     last_shot = current_time;
    // }
}

void Blaster::changeDirection() 
{
    random_device randint;
    uniform_int_distribution<int> random_x(0, 1024);
    uniform_int_distribution<int> random_y(0, 768);

    if (rect.y - rect.h <= 0) 
    {
        move_to.x = random_x(randint);
        move_to.y = SCREEN_HEIGHT;
    }
    else if (rect.y + rect.h >= SCREEN_HEIGHT) 
    {
        move_to.x = random_x(randint);
        move_to.y = 0;
    }
    else if (rect.x - rect.w <= 0) 
    {
        move_to.y = random_y(randint);
        move_to.x = SCREEN_WIDTH;
    }
    else if (rect.x + rect.w >= SCREEN_WIDTH) 
    {
        move_to.y = random_y(randint);
        move_to.x = 0;
    }
}

void Blaster::move() 
{
    changeDirection();

    double center_blaster_x = rect.x + (rect.h / 2);  
    double center_blaster_y = rect.y + (rect.w / 2);
    
    double x_dist = move_to.x - center_blaster_x;
    double y_dist = move_to.y - center_blaster_y;
    double longest = max(abs(x_dist), abs(y_dist));
    
    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;
    
    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));

    setAngle();
}

void Blaster::update()
{
    move();
    shoot();
    updateAABB();
}

void Blaster::setAngle()
{
    // Calculates angle to player
     // int center_x, center_y;
     // float ang;
          
     // center_x = rect.x + (rect.h / 2);
     // center_y = rect.y + (rect.w / 2);
     
     // ang = atan2(center_y - aim_at->second, center_x - aim_at->first);
     // ang = ang * 180 / M_PI;
     
     // angle = (static_cast<int> (ang) + 90)%360;
}
