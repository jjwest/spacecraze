#include "Player.h"

#include <utility>
#include <string>
#include <iostream>

#include "AssetManager.h"
#include "Constants.h"
#include "World.h"

Player::Player(const SDL_Rect& rect)
    :  GameObject(AssetManager::getInstance().getTexture("player"), rect, 1.0),
       pos_x{ static_cast<double>(rect.x) },
       pos_y{ static_cast<double>(rect.y) } {}


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

void Player::setDoubleDamage()
{
    // double_damage.activate();
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
	moveLeft();
    }
    if (key_pressed[SDL_SCANCODE_D] && canMoveRight())
    {
	moveRight();
    }
    if (key_pressed[SDL_SCANCODE_W] && canMoveUp())
    {
	moveUp();
    }
    if (key_pressed[SDL_SCANCODE_S] && canMoveDown())
    {
	moveDown();
    }
}

bool Player::canMoveLeft() const
{
    return hitbox.x - speed >= 0;
}

bool Player::canMoveRight() const
{
    return hitbox.x + hitbox.w + speed <= constants::SCREEN_WIDTH;
}

bool Player::canMoveUp() const
{
    return hitbox.y - speed >= 0;
}

bool Player::canMoveDown() const
{
    return hitbox.y + hitbox.h + speed <= constants::SCREEN_HEIGHT;
}

void Player::moveLeft()
{
    pos_x -= speed;
    hitbox.x = round(pos_x);
}

void Player::moveRight()
{
    pos_x += speed;
    hitbox.x = round(pos_x);
}

void Player::moveUp()
{
    pos_y -= speed;
    hitbox.y = round(pos_y);
}

void Player::moveDown()
{
    pos_y += speed;
    hitbox.y = round(pos_y);
}

void Player::adjustAngle()
{
     int mouse_x, mouse_y;
     SDL_GetMouseState(&mouse_x, &mouse_y);

     int player_center_x = hitbox.x + (hitbox.w / 2);
     int player_center_y = hitbox.y + (hitbox.h / 2);

     double angle_in_radians = atan2(player_center_y - mouse_y, player_center_x - mouse_x);
     double angle_in_degrees = angle_in_radians * 180 / M_PI;
     angle = (static_cast<int>(angle_in_degrees) - 90) % 360;
}

void Player::shoot(World& world)
{
    if (leftMouseButtonPressed() && canShoot())
    {
        int player_center_x = hitbox.x + (hitbox.w / 2);
	world.addPlayerLaser({player_center_x, hitbox.y}, damage);
        last_shot_time = SDL_GetTicks();
    }
}

bool Player::leftMouseButtonPressed() const
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool Player::canShoot() const
{
    Uint32 current_time = SDL_GetTicks();
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
