#ifndef PLAYER_H
#define PLAYER_H

#include "visible_object.h"

#include <SDL2/SDL.h>
#include <string>
#include <list>

class Player: public VisibleObject
{
public:
    Player(int x, int y, SDL_Renderer* renderer);
    ~Player();
    static void updateEach();
    std::pair<int, int> getPos() const;

private:
    static Texture texture;
    static std::list<Player*> players;
    std::list<Player*>::iterator it;

    bool singularity;
    int damage;
    Uint32 last_shot;

    void update();
    void shoot();
    void move();
    void setSingularity();
};

#endif
