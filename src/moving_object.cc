#include "../inc/moving_object.h"

MovingObject::MovingObject(Texture* t, int x, int y,
                             int s, int hp)
    : Sprite(t, x, y), 
      this_object{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w},
    speed{s}, current_hp{hp} {}

bool MovingObject::collides(const AABB& other) const {
    return this_object.intersect(other);
}

bool MovingObject::isDead() const {
    return current_hp <= 0;
}

AABB MovingObject::getAABB() const {
    return this_object;
}

int MovingObject::getScore() const {
    return 0;
}

void MovingObject::reduceHealth(int dmg) {
    current_hp -= dmg;
}

void MovingObject::updateAABB()
{
    this_object = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}

