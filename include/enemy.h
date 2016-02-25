#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "game_object.h"
#include "texture.h"
#include "aabb.h"

class Enemy: public GameObject
{
public:
    Enemy(Texture* t, const Point& pos, double hp, int sc);
    virtual ~Enemy();
    int getScore() const;
    virtual void update(const Point& player_pos) = 0;
    
private:
    int score; 
};


#endif // _ENEMY_H_
