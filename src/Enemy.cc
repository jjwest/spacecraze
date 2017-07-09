#include "Enemy.h"

Enemy::Enemy(Texture* t, const SDL_Rect& rect, float health, int score)
    : GameObject(t, rect, health),
      score{score} {}

Enemy::~Enemy() {}

int Enemy::getScore() const
{
    return score;
}
