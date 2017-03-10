#include "DoubleDamage.h"

DoubleDamage::DoubleDamage(Texture* texture, const SDL_Rect& rect)
    : GameObject(texture, rect, 1.0) {}

std::string DoubleDamage::type() const
{
    return "doubledamage";
}
