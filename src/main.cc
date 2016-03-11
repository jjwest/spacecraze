#include <iostream>

#include "game.h"

int main()
{
    try
    {
        Game game;
        game.run();        
    }
    catch (std::string& s)
    {
        std::cerr << s << std::endl;
    }
    
    return 0;
}
