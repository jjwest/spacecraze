#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include <vector>
#include <string>

class FileManager
{
public:
    FileManager();
    static std::vector<std::string> readHighscoreFromFile(const std::string& path);
    static void writeHighscoreToFile(const std::vector<std::string>& scores,
				     const std::string& path);
};


#endif // _FILE_MANAGER_H_
