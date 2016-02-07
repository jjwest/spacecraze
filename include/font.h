#ifndef _FONT_H_
#define _FONT_H_

#include <SDL2/SDL_ttf.h>
#include <string>

class Font
{
public:
    Font(const std::string& path, int size);
    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;
    ~Font();
    TTF_Font* getFont();

private:
    TTF_Font* font;
};


#endif // _FONT_H_
