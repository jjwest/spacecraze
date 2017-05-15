#include "Powerup.h"

Powerup::Powerup(Texture* texture, const SDL_Rect& rect, PowerupType type)
    : GameObject(texture, rect, 1), type_{type} {}


PowerupType Powerup::type() const
{
    return type_;
}

void Powerup::update()
{
    angle++;
}
