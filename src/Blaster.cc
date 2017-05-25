#include "Blaster.h"

#include <random>

#include "AssetManager.h"
#include "Constants.h"
#include "Globals.h"
#include "World.h"

Blaster::Blaster(const SDL_Rect& rect)
    : Enemy(AssetManager::getInstance().getTexture("blaster"), rect, 15, 40)
{}

void Blaster::update(const Point& player_pos, World& world)
{
    move();
    setAngle(player_pos);
    shoot(player_pos, world);
    updateHitbox(hitbox);
}

void Blaster::move()
{
    changeDirection();

    double center_blaster_x = hitbox.x + (hitbox.w / 2);
    double center_blaster_y = hitbox.y + (hitbox.h / 2);

    double x_dist = move_to.x - center_blaster_x;
    double y_dist = move_to.y - center_blaster_y;
    double longest = std::max( abs(x_dist), abs(y_dist) );

    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;

    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    hitbox.x = hitbox.x + static_cast<int>(round(move_x));
    hitbox.y = hitbox.y + static_cast<int>(round(move_y));
}

void Blaster::changeDirection()
{
    std::random_device rd;
    std::uniform_int_distribution<int> rand_x(0, SCREEN_WIDTH);
    std::uniform_int_distribution<int> rand_y(0, SCREEN_HEIGHT);

    if (hitbox.y - hitbox.h <= 0)
    {
        move_to.x = rand_x(rd);
        move_to.y = SCREEN_HEIGHT;
    }
    else if (hitbox.y + hitbox.h >= SCREEN_HEIGHT)
    {
        move_to.x = rand_x(rd);
        move_to.y = 0;
    }
    else if (hitbox.x - hitbox.w <= 0)
    {
        move_to.y = rand_y(rd);
        move_to.x = SCREEN_WIDTH;
    }
    else if (hitbox.x + hitbox.w >= SCREEN_WIDTH)
    {
        move_to.y = rand_y(rd);
        move_to.x = 0;
    }
}

void Blaster::setAngle(const Point &player_pos)
{
    int center_x = hitbox.x + (hitbox.h / 2);
    int center_y = hitbox.y + (hitbox.w / 2);

    double angle_in_radians = atan2(center_y - player_pos.y, center_x - player_pos.x);
    double angle_in_degrees = angle_in_radians * 180 / M_PI;

    angle = (static_cast<int>(angle_in_degrees) + 90) % 360;
}



void Blaster::shoot(const Point &player_pos, World& world)
{
    if (readyToShoot())
    {
        Point this_pos{ hitbox.x + hitbox.w / 2, hitbox.y  + hitbox.h / 2};
        world.addEnemyLaser(this_pos, player_pos, damage);
        last_shot = SDL_GetTicks();

	if (GLOBAL_SETTINGS.sound_effects)
	{
	    auto shoot_sound = AssetManager::getInstance().getSoundEffect("big_laser");
	    Mix_PlayChannel(-1, shoot_sound, 0);
	}
    }
}

bool Blaster::readyToShoot() const
{
    Uint32 current_time = SDL_GetTicks();
    return current_time - last_shot > shoot_cooldown;
}
