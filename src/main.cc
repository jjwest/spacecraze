#include "../inc/game.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR occurred:" << e.what() 
                  << "\nExiting program." << std::endl;
    }

    return 0;
}

