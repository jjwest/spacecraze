#ifndef _HIGHSCORE_FILE_H_
#define _HIGHSCORE_FILE_H_

#include <vector>
#include <string>

namespace
{
    using score_vec = std::vector<std::pair<std::string, int>>;
}

class HighscoreFile
{
public:
    HighscoreFile() = default;
    static score_vec read();
    static void write(const score_vec& scores);
};


#endif // _HIGHSCORE_FILE_H_
