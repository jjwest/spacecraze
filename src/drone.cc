#include "../include/drone.h"

#include <utility>
#include <math.h>
#include <cmath>
#include <algorithm>

#include "../include/asset_manager.h"

using namespace std;

Drone::Drone(const Point& pos)
    : Enemy(AssetManager::getInstance().getTexture("drone"),
            pos, 6, 10), speed{2} {}

void Drone::move(const Point& player_pos)
{
    float angle_to_player;
    double dest_x = player_pos.x;
    double dest_y = player_pos.y;
    double center_drone_x = rect.x + (rect.h / 2);  
    double center_drone_y = rect.y + (rect.w / 2);

    double x_dist = dest_x - center_drone_x;
    double y_dist = dest_y - center_drone_y;
    double longest = max(abs(x_dist), abs(y_dist));

    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;

    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));

    angle_to_player = atan2(center_drone_y - dest_y, center_drone_x - dest_x);
    angle_to_player = angle_to_player * 180 / M_PI;
    
    angle = (static_cast<int> (angle_to_player)+90)%360;
}

void Drone::update(const Point& player_pos)
{
    move(player_pos);
    updateAABB(rect);
}




