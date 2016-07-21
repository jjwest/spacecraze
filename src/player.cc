#include "player.h"

#include <utility>
#include <string>
#include <iostream>

#include "asset_manager.h"
#include "constants.h"
#include "world.h"

Player::Player(const Point& pos)
    :  GameObject(AssetManager::getInstance().getTexture("player"), pos, 1),
       x_pos{ static_cast<double>(rect.x) },
       y_pos{ static_cast<double>(rect.y) } {}


Point Player::getPos() const
{
    int x = round(rect.x + rect.w / 2);
    int y = round(rect.y + rect.h / 2);

    return {x, y};
}

void Player::update(World* world)
{
    move();
    useSpecial(world);
    shoot(world);
    updateHitbox(rect);
}


void Player::shoot(World* world)
{
    auto current_time = SDL_GetTicks();

    if (readyToShoot()) {
        int center_x = rect.x + rect.h / 2;
        int center_y = rect.y + rect.w / 2;
        Point current_pos{ center_x, center_y };

        world->addPlayerLaser(current_pos, damage);
        last_shot = current_time;
    }
}
void Player::move()
{
    auto state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_D] && rect.x + rect.w + speed <= SCREEN_WIDTH) {
        x_pos += speed;
        rect.x = round(x_pos);
    }
    if (state[SDL_SCANCODE_A] && rect.x - speed >= 0) {
        x_pos -= speed;
        rect.x = round(x_pos);
    }
    if (state[SDL_SCANCODE_W] && rect.y - speed >= 0) {
        y_pos -= speed;
        rect.y = round(y_pos);
    }
    if (state[SDL_SCANCODE_S] && rect.y + rect.h + speed <= SCREEN_HEIGHT) {
        y_pos += speed;
        rect.y = round(y_pos);
    }

    setAngle();
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

void Player::useSpecial(World* world)
{
    if (has_special && rightMouseButtonPressed()) {
	world->killAllEnemies();
	has_special = false;
    }
}

void Player::setAngle()
{
     int x, y;
     SDL_GetMouseState(&x, &y);
     int center_x = rect.x + (rect.h / 2);
     int center_y = rect.y + (rect.w / 2);

     float ang = atan2(center_y - y, center_x - x);
     ang = ang * 180 / M_PI;

     angle = (static_cast<int>(ang) - 90) % 360;
}
