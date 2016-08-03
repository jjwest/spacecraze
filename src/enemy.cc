#include "enemy.h"

Enemy::Enemy(Texture* t, const Point& pos, double health, int score)
    : GameObject(t, pos, health),
      score{score} {}

Enemy::~Enemy() {}

int Enemy::getScore() const
{
    return score;
}
