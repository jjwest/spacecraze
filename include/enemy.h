#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <memory>

#include "game_object.h"
#include "texture.h"
#include "aabb.h"

class Enemy: public GameObject
{
public:
    Enemy(Texture* t, const Point& pos, double hp, int sc);
    Enemy(const Enemy &) = default;
    Enemy(Enemy &&) = default;
    Enemy& operator=(const Enemy &) = delete;
    Enemy& operator=(Enemy &&) = default;

    virtual ~Enemy();
    virtual void update(const Point& player_pos, World& world) = 0;
    int getScore() const;
private:
    int score;
};


#endif // _ENEMY_H_
