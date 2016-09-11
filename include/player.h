#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "game_object.h"

class Player: public GameObject
{
public:
    Player(const SDL_Rect& rect);
    Point getPosition() const;
    void update(World& world);

private:
    bool has_special = true;
    double damage = 2;
    double speed = 4.5;
    double x_pos;
    double y_pos;
    Uint32 shoot_cooldown = 80;
    Uint32 last_shot = 0;

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
    bool readyToShoot() const;
    void useSpecialWeapon(World& world);
};

#endif
