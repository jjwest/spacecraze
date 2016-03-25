#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2/SDL.h>
#include <string>

#include "point.h"
#include "enums.h"

class Button
{
public:
    Button(SDL_Renderer* renderer, int x, int y, const std::string& text,
           const GameStates& act);
    Button(const Button&) = delete;
    Button(Button&&) = default;
    Button& operator=(const Button&) = delete;
    Button& operator=(Button&&) = default;
    ~Button();
    
    GameStates update(const GameStates& current_state);
    void draw(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Texture* normal;
    SDL_Texture* hover;
    GameStates action;

    bool mouseOverButton() const;
};


#endif // _BUTTON_H_
