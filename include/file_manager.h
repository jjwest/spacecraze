#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include <vector>
#include <string>

namespace {
    using score_vec = std::vector<std::pair<std::string, int>>;
}

class FileManager
{
public:
    FileManager() = default;
    score_vec readHighscoreFromFile(const std::string& path);
    void writeHighscoreToFile(const score_vec& scores,
			       const std::string& path);
};


#endif // _FILE_MANAGER_H_
