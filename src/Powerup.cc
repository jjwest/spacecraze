#include "Powerup.h"

Powerup::Powerup(Texture* texture, const SDL_Rect& rect, PowerupType type)
    : GameObject(texture, rect, 1), type{type} {}


PowerupType Powerup::getType() const
{
    return type;
}

void Powerup::update()
{
    angle++;
}
