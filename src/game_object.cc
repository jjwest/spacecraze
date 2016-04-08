#include "game_object.h"

GameObject::GameObject(Texture* t, const Point& pos, double hp)
    : Sprite(t, pos),
      this_aabb{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w},
      health{hp} {}

GameObject::~GameObject() {}

AABB GameObject::getHitbox() const
{
    return this_aabb;
}

bool GameObject::collides(const AABB& other) const
{
    return this_aabb.intersect(other);
}

bool GameObject::isDead() const
{
    return health <= 0;
}

void GameObject::reduceHealth(double damage)
{
    health -= damage;
}

void GameObject::updateHitbox(const SDL_Rect& rect)
{
    this_aabb = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}
