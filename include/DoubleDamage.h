#ifndef _DOUBLEDAMAGE_H_
#define _DOUBLEDAMAGE_H_

#include <string>

#include "Powerup.h"

class DoubleDamage: public Powerup
{
public:
    DoubleDamage(Texture* texture, const SDL_Rect& rect);
    ~DoubleDamage()  {};
    std::string getType() const override;
    void update() override;
};


#endif // _DOUBLEDAMAGE_H_
