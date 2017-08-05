#include <iostream>
#include <string>

#include "Game.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
	return 1;
    }

    return 0;
}
