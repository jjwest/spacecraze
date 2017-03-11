#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "GameObject.h"

class Powerup: public GameObject
{
public:
    Powerup(Texture* texture, const SDL_Rect& rect);
    virtual ~Powerup() {};
    virtual std::string getType() const = 0;
    virtual void update() = 0;
};


#endif // _POWERUP_H_
