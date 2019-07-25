#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

namespace StringUtils {
    std::vector<std::string> split(std::string str, char c)
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
    
    std::string stripDataLabel(std::string line, bool shift = false)
    {
        auto colonIndex = line.find(": ");
        auto offset = shift ? static_cast<std::string::size_type>(2)
                            : static_cast<std::string::size_type>(1);
        return line.substr(colonIndex + offset);
    }
    
    
    std::string chompLine(std::ifstream& streamIn, bool shift = false)
    {
        std::string line;
        getline(streamIn, line);
        return stripDataLabel(line, shift);
    }
    
    std::vector<int> intListToVector(std::string data)
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
};
    
#endif
