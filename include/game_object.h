#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "sprite.h"
#include "texture.h"
#include "point.h"
#include "aabb.h"

class GameObject: public Sprite
{
public:
    GameObject(Texture* t, const Point& pos, double hp);
    virtual ~GameObject();
    AABB getHitbox() const;
    bool collides(const AABB& other) const;
    bool isDead() const;
    void reduceHealth(double damage);
    void updateHitbox(const SDL_Rect& pos);
    
private:
    AABB this_aabb;
    double health;
};


#endif // _GAME_OBJECT_H_
