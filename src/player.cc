#include <function>
#include <utility>
#include <iostream>
#include <SDL2/SDL.h>

#include "../inc/player.h"
#include "../inc/laser.h"
#include <string>

using namespace std;

Player::Player(Texture* t, int x, int y, int s, int hp)
    : Moving_Object(t, x, y, s, hp) carries_singularity{true}, shoot_cooldown{0} {}

bool Player::hasSingularity() const {
    return carries_singularity;
}

void Player::shoot(function<void()>& addFriendlyLaser) {
    if (current_time - shoot_cooldown > 80) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        pair<int, int> direction{mouse_x, mouse_y};
        
        addFriendlyLaser(rect.x, rect.y, damage, direction)
        shoot_cooldown = SDL_GetTicks();
    }
}
void Player::move(const map<string, bool>& actions)  {
    if (actions["RIGHT"] && rect.x < 1024 - speed + rect.w)) {
        rect.x = rect.x + speed;
    }
    if (actions["LEFT"] && rect.x > 0 + speed) {
        rect.x = rect.x - speed;
    }
    if (actions["UP"] && rect.y > 0 + speed) {
        rect.y = rect.y - speed;
    }
    if (actions["DOWN"] && rect.y < 768 - speed + rect.h) {
        rect.y = rect.y + speed;
    }

    setAngle();
}

void Player::update(const map<string, bool>& player_actions,
                    function<void()>& addFriendlyLaser) {
    move(player_actions);
    if (actions.at("SHOOT")) {
        shoot();
    }
    
    // Updates AABB with size slightly smaller than rect
    this_object = AABB(rect.y + 10, rect.x + 10, rect.y + rect.h - 10, rect.x + rect.w - 10);
}

void Player::setAngle() {
     int x, y;
     int center_x, center_y;
     float ang;
     
     SDL_GetMouseState(&x,&y);
     
     center_x = rect.x + (rect.h / 2);
     center_y = rect.y + (rect.w / 2);
     
     ang = atan2(center_y - y, center_x - x);
     ang = ang * 180 / M_PI;
     
     angle = (static_cast<int> (ang) - 90)%360;
}

void Player::setSingularity(bool carries) {
    carries_singularity = carries;
}

pair<int, int> Player::getPos() const {

    int x{ rect.x + rect.h / 2 };
    int y{ rect.y + rect.w / 2 };
    pair<int, int> player_pos{pos_x, pos_y};

    return player_pos;
}
               

