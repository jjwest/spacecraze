#include "../inc/game.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (std::string& e)
    {
        std::cerr << "ERROR occurred: " << e 
                  << "\nExiting program." << std::endl;
    }

    return 0;
}

