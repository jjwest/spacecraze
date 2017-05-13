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

    bool mouseAbove() const;
    void draw(SDL_Renderer* renderer);
    void setText(const std::string& text);
    void setPosition(const Point& pos);
    void addHighlight();
    void removeHighlight();

private:
    bool highlighted = false;
    bool update_text = false;
    std::string text;
    SDL_Rect rect;
    SDL_Texture* texture_normal = nullptr;
    SDL_Texture* texture_hover = nullptr;
};


#endif // _BUTTON_H_
