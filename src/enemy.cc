#include "enemy.h"

Enemy::Enemy(Texture* t, const Point& pos, double hp, int sc)
    : GameObject(t, pos, hp),
      score{sc}
{}

Enemy::~Enemy() {}

int Enemy::getScore() const
{
    return score;
}

