#ifndef _HIGHSCORE_FILE_H_
#define _HIGHSCORE_FILE_H_

#include <vector>
#include <string>

struct ScoreEntry
{
    std::string name;
    int score;
};

class HighscoreFile
{
public:
    HighscoreFile() = default;
    static std::vector<ScoreEntry> read();
    static void write(const std::vector<ScoreEntry>& scores);
};


#endif // _HIGHSCORE_FILE_H_
