#include <iostream>
#include <string>

#include "AssetManager.h"
#include "Game.h"

std::string parseProjectRoot(std::string main_path)
{
    std::string project_name = "spacecraze";
    auto pos = main_path.find(project_name);
    if (pos == main_path.npos)
    {
	throw std::runtime_error("Could not parse project root");
    }

    main_path.erase(
	main_path.begin() + pos + project_name.size(),
	main_path.end()
    );
    return main_path;
}


int main()
{
    try
    {
	auto root = parseProjectRoot(__FILE__);
	std::cerr << "GOT ROOT: " << root << std::endl;
	AssetManager::instance().setProjectRoot(root);
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
