#include "highscore_file.h"

#include <fstream>
#include <sstream>

const std::string FILE_PATH = "highscore.txt";

score_vec HighscoreFile::read()
{
    using namespace std;

    ifstream file{FILE_PATH};
    // Create highscore file if non-existing
    if (!file)
    {
        ofstream new_file{FILE_PATH};
        new_file << "";
        new_file.close();
        file.clear();
        file.open(FILE_PATH);
    }

    score_vec entries;
    string line;
    while (getline(file, line))
    {
        istringstream iss{line};
        string name;
        iss >> name;
	int score;
        iss >> score;
        entries.push_back({name, score});
    }

    return entries;
}

void HighscoreFile::write(const score_vec& scores)
{
    std::ofstream file{FILE_PATH};
    for (const auto& score : scores)
    {
	file << score.first << " " << score.second << '\n';
    }
}
