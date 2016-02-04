#ifndef PLAYER_H
#define PLAYER_H

#include "visible_object.h"

#include <SDL2/SDL.h>
#include <string>
#include <list>
#include <memory>

#include "texture.h"

class Player: public VisibleObject
{
public:
    Player(int x, int y);
    Player(const Player&) = delete;
    ~Player();
    Player& operator=(const Player&) = delete;
    static void updateEach();
    std::pair<int, int> getPos() const;
    void draw(SDL_Renderer* renderer) const;
    void setSingularity();

    static std::list<Player*> list;

private:
    Texture* texture;
    std::list<Player*>::iterator it;
    
    bool singularity;
    int health;
    int damage;
    Uint32 last_shot;

    void update();
    void shoot();
    void move();
};

#endif
