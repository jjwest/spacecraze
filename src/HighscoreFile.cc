#include "HighscoreFile.h"

#include <fstream>
#include <sstream>

const std::string FILE_PATH = "highscore.txt";

std::vector<ScoreEntry> HighscoreFile::read()
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

    std::vector<ScoreEntry> entries;
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

void HighscoreFile::write(const std::vector<ScoreEntry>& entries)
{
    std::ofstream file{FILE_PATH};
    for (const auto& score : entries)
    {
	file << score.name << " " << score.score << '\n';
    }
}
