#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "GameObject.h"

class Player: public GameObject
{
public:
    Player(const SDL_Rect& rect);
    bool hasSpecialWeapon() const;
    Point getPosition() const;
    void setDoubleDamage();
    void update(World& world);

private:
    bool has_special_weapon = true;
    double damage = 2;
    double speed = 4.5;
    double pos_x;
    double pos_y;
    Uint32 shoot_cooldown = 80;
    Uint32 last_shot_time = 0;

    void move();
    bool canMoveLeft() const;
    bool canMoveRight() const;
    bool canMoveUp() const;
    bool canMoveDown() const;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void adjustAngle();
    void shoot(World& world);
    bool leftMouseButtonPressed() const;
    bool canShoot() const;
    void useSpecialWeapon(World& world);
};

#endif
