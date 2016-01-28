#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "text_sprite.h"
#include "texture.h"

class Button: public Text_Sprite {
public:
    Button(SDL_Renderer*, const std::string&, int, int, TTF_Font*, 
           const SDL_Color&, const SDL_Color&);
    ~Button();
    void draw(SDL_Renderer*) const override;

private:
    Texture* texture_highlighted;
    bool cursor_over_button() const;
};

#endif
