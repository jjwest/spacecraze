#include "Blaster.h"

#include <random>

#include "AssetManager.h"
#include "Constants.h"
#include "Globals.h"
#include "World.h"

Blaster::Blaster(const SDL_Rect& rect)
    : Enemy(AssetManager::instance().getTexture("blaster"), rect, 15, 40)
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

    float center_blaster_x = hitbox.x + (hitbox.w / 2);
    float center_blaster_y = hitbox.y + (hitbox.h / 2);

    float x_dist = move_to.x - center_blaster_x;
    float y_dist = move_to.y - center_blaster_y;
    float longest = std::max( abs(x_dist), abs(y_dist) );

    float delta_x = x_dist / longest;
    float delta_y = y_dist /longest;

    float move_x = delta_x * speed;
    float move_y = delta_y * speed;

    hitbox.x = hitbox.x + static_cast<int>(round(move_x));
    hitbox.y = hitbox.y + static_cast<int>(round(move_y));
}

void Blaster::changeDirection()
{
    static std::random_device rd;
    static std::uniform_int_distribution<int> rand_x(0, SCREEN_WIDTH);
    static std::uniform_int_distribution<int> rand_y(0, SCREEN_HEIGHT);

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
    int center_x = hitbox.x + (hitbox.w / 2);
    int center_y = hitbox.y + (hitbox.h / 2);

    float angle_in_radians = atan2(center_y - player_pos.y, center_x - player_pos.x);
    float angle_in_degrees = angle_in_radians * 180 / M_PI;

    angle = (static_cast<int>(angle_in_degrees) + 90) % 360;
}



void Blaster::shoot(const Point &player_pos, World& world)
{
    Uint32 current_time = SDL_GetTicks();
    bool ready_to_shoot = current_time - last_shot > shoot_cooldown;

    if (ready_to_shoot)
    {
	int center_x = hitbox.x + hitbox.w / 2;
	int center_y = hitbox.y + hitbox.h / 2;
        Point this_pos{center_x, center_y};
        world.addEnemyLaser(this_pos, player_pos, damage);
        last_shot = current_time;

	if (GLOBAL_SETTINGS.sound_effects)
	{
	    auto shoot_sound = AssetManager::instance().getSoundEffect("big_laser");
	    Mix_PlayChannel(-1, shoot_sound, 0);
	}
    }
}
