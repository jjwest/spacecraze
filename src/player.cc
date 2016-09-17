#include "player.h"

#include <utility>
#include <string>
#include <iostream>

#include "assets.h"
#include "constants.h"
#include "world.h"

Player::Player(const SDL_Rect& rect)
    :  GameObject(Assets::getInstance().getTexture("player"), rect, 1.0),
       x_pos{ static_cast<double>(rect.x) },
       y_pos{ static_cast<double>(rect.y) } {}


Point Player::getPosition() const
{
    int center_x = round( rect.x + (rect.w / 2) );
    int center_y = round( rect.y + (rect.h / 2) );

    return {center_x, center_y};
}

void Player::update(World& world)
{
    move();
    adjustAngle();
    shoot(world);
    useSpecialWeapon(world);
    updateHitbox(rect);
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
    return rect.x - speed >= 0;
}

bool Player::canMoveRight() const
{
    return rect.x + rect.w + speed <= SCREEN_WIDTH;
}
bool Player::canMoveUp() const
{
    return rect.y - speed >= 0;
}
bool Player::canMoveDown() const
{
    return rect.y + rect.h + speed <= SCREEN_HEIGHT;
}

void Player::moveLeft()
{
    x_pos -= speed;
    rect.x = round(x_pos);
}

void Player::moveRight()
{
    x_pos += speed;
    rect.x = round(x_pos);
}

void Player::moveUp()
{
    y_pos -= speed;
    rect.y = round(y_pos);
}

void Player::moveDown()
{
    y_pos += speed;
    rect.y = round(y_pos);
}

void Player::adjustAngle()
{
     int x, y;
     SDL_GetMouseState(&x, &y);
     int center_x = rect.x + (rect.w / 2);
     int center_y = rect.y + (rect.h / 2);

     angle = atan2(center_y - y, center_x - x);
     angle = angle * 180 / M_PI;
     angle = (static_cast<int>(angle) - 90) % 360;
}

void Player::shoot(World& world)
{
    if (readyToShoot())
    {
        int center_x = rect.x + (rect.w / 2);
        int center_y = rect.y + (rect.h / 2);
        Point current_pos{ center_x, center_y };

        world.addPlayerLaser({center_x, rect.y}, damage);
        last_shot = SDL_GetTicks();
    }
}

bool Player::readyToShoot() const
{
    auto current_time = SDL_GetTicks();

    return SDL_GetMouseState(NULL, NULL)
        & SDL_BUTTON(SDL_BUTTON_LEFT)
        && current_time - last_shot > shoot_cooldown;
}

bool rightMouseButtonPressed()
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void Player::useSpecialWeapon(World& world)
{
    if (has_special && rightMouseButtonPressed())
    {
	world.killAllEnemies();
	has_special = false;
    }
}
