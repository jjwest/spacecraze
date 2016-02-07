#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "visible_object.h"
#include "texture.h"
#include "aabb.h"

class Enemy: public VisibleObject
{
public:
    Enemy(Texture* t, int x, int y, double hp, int sp, int sc);
    virtual ~Enemy();
    bool isDead() const;
    int getScore() const;
    
protected:
    AABB this_aabb;
    double health;
    int speed;
    int score;

    void updateAABB();
};


#endif // _ENEMY_H_
