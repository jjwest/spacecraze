#include "blaster.h"

#include <random>

#include "constants.h"
#include "asset_manager.h"
#include "world.h"

Blaster::Blaster(const Point &pos)
    : Enemy(AssetManager::getInstance().getTexture("blaster"), pos, 15, 40)
{}

void Blaster::update(const Point &player_pos, World* lasers)
{
    move();
    setAngle(player_pos);
    shoot(player_pos, lasers);
    updateHitbox(rect);
}

void Blaster::shoot(const Point &player_pos, World* world)
{
    Uint32 current_time = SDL_GetTicks();

    if (current_time - last_shot > shoot_cooldown)
    {
        Point this_pos {rect.x, rect.y};
        world->addEnemyLaser(this_pos, player_pos, damage);
        last_shot = current_time;
    }
}

void Blaster::changeDirection()
{
    std::random_device rd;
    std::uniform_int_distribution<int> rand_x(0, SCREEN_WIDTH);
    std::uniform_int_distribution<int> rand_y(0, SCREEN_HEIGHT);

    if (rect.y - rect.h <= 0)
    {
        move_to.x = rand_x(rd);
        move_to.y = SCREEN_HEIGHT;
    }
    else if (rect.y + rect.h >= SCREEN_HEIGHT)
    {
        move_to.x = rand_x(rd);
        move_to.y = 0;
    }
    else if (rect.x - rect.w <= 0)
    {
        move_to.y = rand_y(rd);
        move_to.x = SCREEN_WIDTH;
    }
    else if (rect.x + rect.w >= SCREEN_WIDTH)
    {
        move_to.y = rand_y(rd);
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
    double longest = std::max( abs(x_dist), abs(y_dist) );

    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;

    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));
}

void Blaster::setAngle(const Point &player_pos)
{
    int center_x = rect.x + (rect.h / 2);
    int center_y = rect.y + (rect.w / 2);

    float ang = atan2(center_y - player_pos.y, center_x - player_pos.x);
    ang = ang * 180 / M_PI;

    angle = (static_cast<int>(ang) + 90) % 360;
}
