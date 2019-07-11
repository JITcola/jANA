#include "JobFileReader.h"

#include <string>
#include <vector>
#include <fstream>
#include <utility>

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

    std::ifstream jobFile {"Job" + std::to_string(jobId) + ".job"};

    getline(jobFile, currentLine);
    
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    precision = data == " double" ? "double" : "multiprecision";

    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    multiprecisionBits = std::stoi(data);

    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    sampleRate = std::stoi(data);

    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    renderLength = std::stoi(data);

    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    if (data != " ") {
        if (data.find(',') == std::string::npos)
            modOutDependencyIds.push_back(std::stoi(data));
        else {
            auto nextCommaIndex = data.find(',');
            while (nextCommaIndex != std::string::npos) {
                modOutDependencyIds.push_back(std::stoi(data.substr(
                    static_cast<std::string::size_type>(0), nextCommaIndex)));
                data = data.substr(nextCommaIndex + 
                    static_cast<std::string::size_type>(1));
                nextCommaIndex = data.find(',');
            }
            modOutDependencyIds.push_back(std::stoi(data));
        }
    }

    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    if (data != " ") {
        if (data.find(',') == std::string::npos)
            modOutProductIds.push_back(std::stoi(data));
        else {
            auto nextCommaIndex = data.find(',');
            while (nextCommaIndex != std::string::npos) {
                modOutProductIds.push_back(std::stoi(data.substr(
                    static_cast<std::string::size_type(0), nextCommaIndex)));
                data = data.substr(nextCommaIndex +
                    static_cast<std::string::size_type>(1));
                nextCommaIndex = data.find(',');
            }
            modOutProductIds.push_back(std::stoi(data));
        }
    }

    JobInfo jobInfo;

            





}

std::string stripDataLabel(std::string line)
{
    return line.substr(line.find(": ") + static_cast<std::string::size_type>(1));
}
