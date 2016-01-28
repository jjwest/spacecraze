#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <utility>
#include <map>

#include "aabb.h"
#include "sprite.h"
#include "texture.h"

class MovingObject: public Sprite {
public:
    MovingObject(Texture*, int, int, int, int, double);
    virtual ~MovingObject() = default;
    AABB getAABB() const;
    bool collides(const AABB&) const;
    bool isDead() const;
    virtual int getScore() const;
    void reduceHealth(int);
        
protected:
    AABB this_object;
    int speed;
    int current_hp;
    void updateAABB();
};

#endif
