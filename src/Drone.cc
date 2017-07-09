#include "Drone.h"

#include <utility>
#include <math.h>
#include <cmath>
#include <algorithm>

#include "AssetManager.h"

Drone::Drone(const SDL_Rect& rect)
    : Enemy(AssetManager::getInstance().getTexture("drone"), rect, 6, 10) {}

void Drone::update(const Point& player_pos, World&)
{
    move(player_pos);
    updateHitbox(hitbox);
}

void Drone::move(const Point& player_pos)
{
    float dest_x = player_pos.x;
    float dest_y = player_pos.y;
    float center_drone_x = hitbox.x + (hitbox.h / 2);
    float center_drone_y = hitbox.y + (hitbox.w / 2);

    float x_dist = dest_x - center_drone_x;
    float y_dist = dest_y - center_drone_y;
    int longest = std::max( abs( int(x_dist) ), abs( int(y_dist) ) );

    float delta_x = x_dist / longest;
    float delta_y = y_dist / longest;

    float move_x = delta_x * speed;
    float move_y = delta_y * speed;

    hitbox.x = hitbox.x + static_cast<int>(round(move_x));
    hitbox.y = hitbox.y + static_cast<int>(round(move_y));

    float angle_to_player = atan2(center_drone_y - dest_y, center_drone_x - dest_x);
    angle_to_player = angle_to_player * 180 / M_PI;

    angle = (static_cast<int>(angle_to_player) + 90) % 360;
}
