#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "sprite.h"
#include "texture.h"
#include "point.h"
#include "aabb.h"

// We must forward declare a World class so game objects
// can get a pointer to the world that contains them, since
// two class definitions cannot directly include each other.
class World;

class GameObject: public Sprite
{
public:
    GameObject(Texture* t, const Point& pos, double hp);
    virtual ~GameObject();
    AABB getHitbox() const;
    bool collides(const AABB& other) const;
    bool isDead() const;
    void kill();
    void reduceHealth(double damage);
    void updateHitbox(const SDL_Rect& pos);

private:
    AABB this_aabb;
    double health;
};


#endif // _GAME_OBJECT_H_
