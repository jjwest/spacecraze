#ifndef _DOUBLEDAMAGE_H_
#define _DOUBLEDAMAGE_H_

#include <string>

#include "GameObject.h"

class DoubleDamage: GameObject
{
public:
    DoubleDamage(Texture* texture, const SDL_Rect& rect);
    std::string type() const;
};


#endif // _DOUBLEDAMAGE_H_
