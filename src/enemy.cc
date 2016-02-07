#include "../include/enemy.h"

Enemy::Enemy(Texture* t, int x, int y, double hp, int sp, int sc)
    : VisibleObject(t, x, y), 
      this_aabb{rect.y, rect.x, rect.y + rect.h, rect.x + rect.w}, 
      health{hp}, speed{sp}, score{sc} {}

bool Enemy::isDead() const
{
    return health <= 0;
}

int Enemy::getScore() const
{
    return score;
}

void Enemy::updateAABB()
{
    this_aabb = AABB(rect.y, rect.x, rect.y + rect.h, rect.x + rect.w);
}
