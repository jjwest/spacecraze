#include "Player.h"

#include <string>
#include <utility>

#include "AssetManager.h"
#include "Constants.h"
#include "Settings.h"
#include "World.h"

Player::Player(const SDL_Rect& hitbox)
    :  GameObject(AssetManager::getInstance().getTexture("player"), hitbox, 1.0),
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

    if (key_pressed[SDL_SCANCODE_A] && canMoveLeft())
    {
	pos_x -= speed;
	hitbox.x = round(pos_x);
    }
    if (key_pressed[SDL_SCANCODE_D] && canMoveRight())
    {
	pos_x += speed;
	hitbox.x = round(pos_x);
    }
    if (key_pressed[SDL_SCANCODE_W] && canMoveUp())
    {
	pos_y -= speed;
	hitbox.y = round(pos_y);
    }
    if (key_pressed[SDL_SCANCODE_S] && canMoveDown())
    {
	pos_y += speed;
	hitbox.y = round(pos_y);
    }
}

bool Player::canMoveLeft() const
{
    return hitbox.x - speed >= 0;
}

bool Player::canMoveRight() const
{
    return hitbox.x + hitbox.w + speed <= SCREEN_WIDTH;
}

bool Player::canMoveUp() const
{
    return hitbox.y - speed >= 0;
}

bool Player::canMoveDown() const
{
    return hitbox.y + hitbox.h + speed <= SCREEN_HEIGHT;
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
    if (leftMouseButtonPressed() && canShoot())
    {
        auto player_center_x = hitbox.x + (hitbox.w / 2);
	world.addPlayerLaser({player_center_x, hitbox.y}, damage);
        last_shot_time = SDL_GetTicks();

	if (GLOBAL_SETTINGS.sound_effects)
	{
	    auto shoot_sound = AssetManager::getInstance().getSoundEffect("small_laser");
	    Mix_PlayChannel(-1, shoot_sound, 0);
	}
    }
}

bool Player::leftMouseButtonPressed() const
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool Player::canShoot() const
{
    auto current_time = SDL_GetTicks();
    return current_time - last_shot_time > shoot_cooldown;
}

bool rightMouseButtonPressed()
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void Player::useSpecialWeapon(World& world)
{
    if (has_special_weapon && rightMouseButtonPressed())
    {
	world.clearEnemies();
	has_special_weapon = false;
    }
}
