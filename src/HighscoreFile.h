#ifndef _HIGHSCORE_FILE_H_
#define _HIGHSCORE_FILE_H_

#include <vector>
#include <string>

using score_t = std::vector<std::pair<std::string, int>>;

class HighscoreFile
{
public:
    HighscoreFile() = default;
    static score_t read();
    static void write(const score_t& scores);
};


#endif // _HIGHSCORE_FILE_H_
