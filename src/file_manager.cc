#include "file_manager.h"

#include <fstream>
#include <sstream>

#include "cppformat/format.h"

std::vector<std::string> FileManager::readHighscore(const std::string& path)
{
    using namespace std;

    ifstream ifs{path};
    if (!ifs)
    {
        ofstream new_file{path};
        new_file << "";
        new_file.close();
        ifs.clear();
        ifs.open(path);
    }

    vector<string> entries;
    string line;
    while (getline(ifs, line))
    {
        istringstream iss{line};
        string name, score;
        iss >> name;
        iss >> score;
        string entry = fmt::format("{:<20} {}", name, score);
        entries.push_back(entry);
    }

    return entries;
}

void FileManager::writeHighscore(const std::vector<std::string>& scores,
				       const std::string& path)
{
    std::ofstream file{path};
    for (const auto& score : scores)
    {
	file << score << '\n';
    }
}
