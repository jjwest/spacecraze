#include "DoubleDamage.h"

DoubleDamage::DoubleDamage(Texture* texture, const SDL_Rect& rect)
    : Powerup(texture, rect) {}

std::string DoubleDamage::getType() const
{
    return "doubledamage";
}

void DoubleDamage::update()
{
    angle++;
}
