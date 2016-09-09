#include "drone.h"

#include <utility>
#include <math.h>
#include <cmath>
#include <algorithm>

#include "assets.h"

Drone::Drone(const Point& pos)
    : Enemy(Assets::getInstance().getTexture("drone"), pos, 6, 10)
{}

void Drone::update(const Point& player_pos, World&)
{
    move(player_pos);
    updateHitbox(rect);
}

void Drone::move(const Point& player_pos)
{
    double dest_x = player_pos.x;
    double dest_y = player_pos.y;
    double center_drone_x = rect.x + (rect.h / 2);
    double center_drone_y = rect.y + (rect.w / 2);

    double x_dist = dest_x - center_drone_x;
    double y_dist = dest_y - center_drone_y;
    double longest = std::max(abs(x_dist), abs(y_dist));

    double delta_x = x_dist / longest;
    double delta_y = y_dist / longest;

    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));

    float angle_to_player = atan2(center_drone_y - dest_y, center_drone_x - dest_x);
    angle_to_player = angle_to_player * 180 / M_PI;

    angle = (static_cast<int>(angle_to_player) + 90) % 360;
}
