#include "../include/game_object.h"

GameObject::GameObject(Texture* t, const Point& pos) 
    : texture{t}, angle{0}, rect{pos.x, pos.y, texture->getHeight(),
                                    texture->getWidth()} {}

GameObject::~GameObject() {}

void GameObject::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, 
                     &rect, angle, NULL, SDL_FLIP_NONE);
}
