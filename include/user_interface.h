#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <SDL2/SDL.h>
#include <memory>

#include "rendered_text.h"
#include "sprite.h"

class UserInterface
{
public:
    UserInterface(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer, int current_score);

private:
    int score = 0;
    std::unique_ptr<RenderedText> rendered_score;

    void updateScoreTexture(SDL_Renderer* renderer, int new_score);
};


#endif // _USER_INTERFACE_H_
