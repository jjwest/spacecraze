#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2/SDL.h>
#include <string>

#include "Point.h"
#include "Enums.h"

class Button
{
public:
    Button() = default;
    Button(const Button&) = delete;
    Button(Button&&) = default;
    Button& operator=(const Button&) = delete;
    Button& operator=(Button&&) = default;
    ~Button();

    bool pressed() const;
    void draw(SDL_Renderer* renderer);
    void setText(SDL_Renderer* renderer, const std::string& text);
    void setPosition(const Point& pos);

private:
    SDL_Rect rect;
    SDL_Texture* texture_normal = nullptr;
    SDL_Texture* texture_hover = nullptr;

    bool mouseOverButton() const;
};


#endif // _BUTTON_H_
