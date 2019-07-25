#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

namespace StringUtils {
    std::vector<std::string> split(std::string str, char c);
    std::string stripDataLabel(std::string line, bool shift = false);
    std::string chompLine(std::ifstream& streamIn, bool shift = false);
    std::vector<int> intListToVector(std::string data);
};
    
#endif
