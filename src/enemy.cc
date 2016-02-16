#include "../include/enemy.h"

Enemy::Enemy(Texture* t, const Point& pos, double hp, int sp, int sc)
    : VisibleObject(t, pos), 
      this_aabb{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w}, 
      health{hp}, speed{sp}, score{sc} {}

Enemy::~Enemy() {}

AABB Enemy::getAABB() const
{
    return this_aabb;
}

bool Enemy::collides(const AABB& other) const
{
    return this_aabb.intersect(other);
}

bool Enemy::isDead() const
{
    return health <= 0;
}

int Enemy::getScore() const
{
    return score;
}

void Enemy::reduceHealth(double damage)
{
    health -= damage;
}

void Enemy::updateAABB()
{
    this_aabb = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}
