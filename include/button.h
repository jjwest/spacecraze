#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2/SDL.h>
#include <string>

#include "point.h"
#include "enums.h"

class Button
{
public:
    Button(SDL_Renderer* renderer, const Point& pos, const std::string& text,
           const State& act);
    Button(const Button&) = delete;
    Button(Button&&) = default;
    Button& operator=(const Button&) = delete;
    Button& operator=(Button&&) = default;
    ~Button();
    
    State update(const State& current_state);
    void draw(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Texture* normal;
    SDL_Texture* hover;
    State action;

    bool mouseOverButton() const;
};


#endif // _BUTTON_H_
