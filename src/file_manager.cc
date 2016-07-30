#include "file_manager.h"

#include <fstream>
#include <sstream>

score_vec FileManager::readHighscore(const std::string& path)
{
    using namespace std;

    ifstream ifs{path};
    // Create highscore file if non-existing
    if (!ifs)
    {
        ofstream new_file{path};
        new_file << "";
        new_file.close();
        ifs.clear();
        ifs.open(path);
    }

    score_vec entries;
    string line;
    while (getline(ifs, line))
    {
        istringstream iss{line};
        string name;
        iss >> name;
	int score;
        iss >> score;
        entries.push_back(make_pair(name, score));
    }

    return entries;
}

void FileManager::writeHighscore(const score_vec& scores,
				 const std::string& path)
{
    std::ofstream file{path};
    for (const auto& score : scores)
    {
	file << score.first << " " << score.second << '\n';
    }
}
