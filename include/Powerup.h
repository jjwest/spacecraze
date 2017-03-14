#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "GameObject.h"

enum PowerupType {
    BONUS_DAMAGE
};

class Powerup: public GameObject
{
public:
    Powerup(Texture* texture, const SDL_Rect& rect, PowerupType type);
    PowerupType getType() const;
    void update();
private:
    PowerupType type;
};


#endif // _POWERUP_H_
