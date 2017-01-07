#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Sprite.h"
#include "Texture.h"
#include "Point.h"
#include "AABB.h"

// We must forward declare a non-defined  World class so game objects
// can get a reference to the world that contains them, since
// two class definitions cannot directly include each other.
class World;

class GameObject: public Sprite
{
public:
    GameObject(Texture* t, const SDL_Rect& rect, double hp);
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
