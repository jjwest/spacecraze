#include "Font.h"

using namespace std;

Font::Font(const string& path, int size)
    : font{ TTF_OpenFont( path.c_str(), size ) }
{
    if (font == NULL)
    {
        throw "Could not load font " + path;
    }
}

Font::~Font()
{
    TTF_CloseFont(font);
}

TTF_Font* Font::getFont()
{
    return font;
}
