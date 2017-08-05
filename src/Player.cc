#include "Player.h"

#include <string>
#include <utility>

#include "AssetManager.h"
#include "Constants.h"
#include "Globals.h"
#include "World.h"

Player::Player(const SDL_Rect& hitbox)
    :  GameObject(AssetManager::instance().getTexture("player"), hitbox, 1.0),
       pos_x{ static_cast<float>(hitbox.x) },
       pos_y{ static_cast<float>(hitbox.y) } {}


bool Player::hasSpecialWeapon() const
{
    return has_special_weapon;
}

Point Player::getPosition() const
{
    int center_x = round( hitbox.x + (hitbox.w / 2) );
    int center_y = round( hitbox.y + (hitbox.h / 2) );

    return {center_x, center_y};
}

void Player::increaseDamage()
{
    ++damage;
}

void Player::update(World& world)
{
    move();
    adjustAngle();
    shoot(world);
    useSpecialWeapon(world);
    updateHitbox(hitbox);
}


void Player::move()
{
    auto key_pressed = SDL_GetKeyboardState(NULL);

    bool can_move_left = hitbox.x - speed >= 0;
    if (key_pressed[SDL_SCANCODE_A] && can_move_left)
    {
	pos_x -= speed;
	hitbox.x = round(pos_x);
    }

    bool can_move_right = hitbox.x + hitbox.w + speed <= SCREEN_WIDTH;
    if (key_pressed[SDL_SCANCODE_D] && can_move_right)
    {
	pos_x += speed;
	hitbox.x = round(pos_x);
    }

    bool can_move_up = hitbox.y - speed >= 0;
    if (key_pressed[SDL_SCANCODE_W] && can_move_up)
    {
	pos_y -= speed;
	hitbox.y = round(pos_y);
    }

    bool can_move_down = hitbox.y + hitbox.h + speed <= SCREEN_HEIGHT;
    if (key_pressed[SDL_SCANCODE_S] && can_move_down)
    {
	pos_y += speed;
	hitbox.y = round(pos_y);
    }
}

void Player::adjustAngle()
{
     int mouse_x, mouse_y;
     SDL_GetMouseState(&mouse_x, &mouse_y);

     auto player_center_x = hitbox.x + (hitbox.w / 2);
     auto player_center_y = hitbox.y + (hitbox.h / 2);
     auto angle_in_radians = atan2(player_center_y - mouse_y, player_center_x - mouse_x);
     auto angle_in_degrees = angle_in_radians * 180 / M_PI;

     angle = (static_cast<int>(angle_in_degrees) - 90) % 360;
}

void Player::shoot(World& world)
{
    auto current_time = SDL_GetTicks();
    bool can_shoot = current_time - last_shot_time > shoot_cooldown;
    bool left_mouse_button_pressed = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);

    if (left_mouse_button_pressed && can_shoot)
    {
        auto player_center_x = hitbox.x + (hitbox.w / 2);
	world.addPlayerLaser({player_center_x, hitbox.y}, damage);
        last_shot_time = current_time;

	if (GLOBAL_SETTINGS.sound_effects)
	{
	    auto shoot_sound = AssetManager::instance().getSoundEffect("small_laser");
	    Mix_PlayChannel(-1, shoot_sound, 0);
	}
    }
}

void Player::useSpecialWeapon(World& world)
{
    bool right_mouse_button_pressed = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
    if (has_special_weapon && right_mouse_button_pressed)
    {
	world.clearEnemies();
	has_special_weapon = false;
    }
}
