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

    bool mouseOver() const;
    void draw(SDL_Renderer* renderer);
    void setText(const std::string& text);
    void setPosition(int x, int y);
    void addHighlight();
    void removeHighlight();

private:
    SDL_Rect rect;
    SDL_Texture* texture_highlighted = nullptr;
    SDL_Texture* texture_normal = nullptr;

    bool highlighted = false;
    bool text_modified = false;
    std::string text;
};


#endif // _BUTTON_H_
