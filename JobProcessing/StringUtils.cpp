#include "StringUtils.h"

#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> StringUtils::split(std::string str, char c)
{
    std::vector<std::string> result;
    auto nextIndex = str.find(c);
    while (nextIndex != std::string::npos) {
        result.push_back(str.substr(
            static_cast<std::string::size_type>(0), nextIndex));
        str = 
            nextIndex == static_cast<std::string::size_type>(str.length()-1) 
            ? ""
            : str.substr(nextIndex + static_cast<std::string::size_type>(1));
        nextIndex = str.find(c);
    }
    result.push_back(str);
    return result;
}

std::string StringUtils::stripDataLabel(std::string line, bool shift)
{
    auto colonIndex = line.find(": ");
    auto offset = shift ? static_cast<std::string::size_type>(2)
                        : static_cast<std::string::size_type>(1);
    return line.substr(colonIndex + offset);
}


std::string StringUtils::chompLine(std::ifstream& streamIn, bool shift)
{
    std::string line;
    getline(streamIn, line);
    return stripDataLabel(line, shift);
}

std::vector<int> StringUtils::intListToVector(std::string data)
{
    std::vector<int> result;
    if (data != " ") {
        if (data.find(',') == std::string::npos)
            result.push_back(std::stoi(data));
        else {
            auto nextCommaIndex = data.find(',');
            while (nextCommaIndex != std::string::npos) {
                result.push_back(std::stoi(data.substr(
                    static_cast<std::string::size_type>(0), nextCommaIndex)));
                data = data.substr(nextCommaIndex + 
                    static_cast<std::string::size_type>(1));
                nextCommaIndex = data.find(',');
            }
            result.push_back(std::stoi(data));
        }
    }
    return result;
}
