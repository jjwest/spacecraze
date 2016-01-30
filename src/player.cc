#include "../inc/player.h"

#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <string>

using namespace std;

Player::Player(int x, int y, SDL_Renderer* renderer): singularity{true}, damage{2}, last_shot{0} 
{
    if (players.empty()) {
        string path {"../sprites/playership.png"};

        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == NULL) {
            throw invalid_argument("Could not load sprite: " + path);
        }
        
        texture.texture = SDL_CreateTextureFromSurface(renderer, surface);
        texture.width = surface->w;
        texture.height = surface->h;
        SDL_FreeSurface(surface);
    }
    rect.x = x;
    rect.y = y;
    rect.w = texture.width;
    rect.h = texture.height;

    players.push_front(this);
    it = players.begin();
}

Player::~Player()
{
    players.erase(it);
    if (players.empty()) {
        SDL_DestroyTexture(texture.texture);
    }
}

void Player::updateEach()
{
    for (auto p : players) {
        p->update();
    }
}

void Player::shoot()
{
    Uint32 current_time{ SDL_GetTicks() };

    if (current_time - last_shot > 80) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        pair<int, int> direction{mouse_x, mouse_y};


        last_shot = current_time;
    }
}
void Player::move()  
{
    // if (player_actions.at("RIGHT") && rect.x < SCREEN_WIDTH - speed + rect.w) {
    //     rect.x = rect.x + speed;
    // }
    // if (player_actions.at("LEFT") && rect.x > 0 + speed) {
    //     rect.x = rect.x - speed;
    // }
    // if (player_actions.at("UP") && rect.y > 0 + speed) {
    //     rect.y = rect.y - speed;
    // }
    // if (player_actions.at("DOWN") && rect.y < 768 - speed + rect.h) {
    //     rect.y = rect.y + speed;
    // }

    // setAngle();
}

void Player::update()
{
    // move(player_actions);
    // if (player_actions.at("SHOOT")) {
    //     shoot(world);
    // }
    // // Updates AABB with size slightly smaller than rect
    // this_object = AABB(rect.y + 10, rect.x + 10, rect.y + rect.h - 10, rect.x + rect.w - 10);
}

// void Player::setAngle() 
// {
//      // int x, y;
//      // int center_x, center_y;
//      // float ang;
     
//      // SDL_GetMouseState(&x,&y);
     
//      // center_x = rect.x + (rect.h / 2);
//      // center_y = rect.y + (rect.w / 2);
     
//      // ang = atan2(center_y - y, center_x - x);
//      // ang = ang * 180 / M_PI;
     
//      // angle = (static_cast<int> (ang) - 90)%360;
// }

void Player::setSingularity() {}

pair<int, int> Player::getPos() const 
{
    int pos_x{ rect.x + rect.h / 2 };
    int pos_y{ rect.y + rect.w / 2 };
    pair<int, int> player_pos{pos_x, pos_y};

    return player_pos;
}
               

