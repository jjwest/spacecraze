#include "GameObject.h"

GameObject::GameObject(Texture* t, const SDL_Rect& rect, double hp)
    : Sprite(t, rect),
      aabb{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w},
      health{hp} {}

GameObject::~GameObject() {}

AABB GameObject::getHitbox() const
{
    return aabb;
}

bool GameObject::collides(const GameObject& other) const
{
    return aabb.intersect(other.aabb);
}

bool GameObject::isDead() const
{
    return health <= 0;
}

void GameObject::kill()
{
    health = 0;
}

void GameObject::reduceHealth(double damage)
{
    health -= damage;
}

void GameObject::updateHitbox(const SDL_Rect& rect)
{
    aabb = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}
