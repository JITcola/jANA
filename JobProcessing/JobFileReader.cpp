#include "JobFileReader.h"

#include <string>
#include <vector>
#include <fstream>
#include <utility>

std::string stripDataLabel(std::string line, bool shift = 0);
std::string chompLine(std::ifstream& streamIn, bool shift = 0);
std::vector<int> intListToVector(std::string data);

EvaluatorTemplate JobFileReader::readJobFile(int jobId)
{
    std::string currentLine;
    std::string data;
    int id {jobId};
    std::string precision;
    int multiprecisionBits;
    int sampleRate;
    int renderLength;
    std::vector<int> modOutDependencyIds;
    std::vector<int> modOutProductIds;

    EvaluatorTemplate result;

    std::ifstream jobFile {"Job" + std::to_string(jobId) + ".job"};
    getline(jobFile, currentLine);
    
    data = chompLine(jobFile, true);
    precision = data;

    data = chompLine(jobFile);
    multiprecisionBits = std::stoi(data);

    data = chompLine(jobFile);
    sampleRate = std::stoi(data);

    data = chompLine(jobFile);
    renderLength = std::stoi(data);

    data = chompLine(jobFile);
    modOutDependencyIds = intListToVector(data);

    data = chompLine(jobFile);
    modOutProductIds = intListToVector(data);

    jobFile.close();
    return result;
}

std::string stripDataLabel(std::string line, bool shift)
{
    return line.substr(line.find(": ") + static_cast<std::string::size_type>(1) +
           shift ? static_cast<std::string::size_type>(1) :
                   static_cast<std::string::size_type>(0));
}

std::string chompLine(std::ifstream& streamIn, bool shift)
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
