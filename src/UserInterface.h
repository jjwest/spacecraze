#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <SDL2/SDL.h>
#include <memory>

#include "Text.h"
#include "Sprite.h"

class UserInterface
{
public:
    UserInterface();
    void draw(SDL_Renderer* renderer);
    void update(int new_score, bool has_special);

private:
    bool player_has_special = true;
    bool score_changed = true;
    int score = 0;
    Sprite special_weapon;
    std::unique_ptr<Text> rendered_score;
};


#endif // _USER_INTERFACE_H_
