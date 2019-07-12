#include "JobFileReader.h"

#include <string>
#include <vector>
#include <fstream>
#include <utility>

std::vector<std::string> split(std::string str, char c);
std::string stripDataLabel(std::string line, bool shift = false);
std::string chompLine(std::ifstream& streamIn, bool shift = false);
std::vector<int> intListToVector(std::string data);
ModuleRecord processModuleInfo(std::ifstream& streamIn);
std::vector<std::pair<std::string, std::string>> 
    processParameterInfo(std::ifstream& streamIn);
std::vector<std::pair<std::pair<std::string, int>, int>>
    processDependencyInfo(std::ifstream& streamIn);

EvaluatorTemplate JobFileReader::readJobFile(int jobId)
{
    std::string currentLine;
    EvaluatorTemplate result;

    std::ifstream jobFile {"Job" + std::to_string(jobId) + ".job"};
    getline(jobFile, currentLine);
    
    std::string precision = chompLine(jobFile, true);
    int multiprecisionBits = std::stoi(chompLine(jobFile));
    int sampleRate = std::stoi(chompLine(jobFile));
    int renderLength = std::stoi(chompLine(jobFile));
    std::vector<int> modOutDependencyIds = intListToVector(chompLine(jobFile));
    std::vector<int> modOutProductIds = intListToVector(chompLine(jobFile));

    JobInfo resultJobInfo(precision, multiprecisionBits, sampleRate, 
                          renderLength, modOutDependencyIds,
                          modOutProductIds);
    result.jobInfo = resultJobInfo;

    std::vector<ModuleRecord> resultModuleRecords;
    getline(jobFile, currentLine);
    while(jobFile) {
        ModuleRecord newModuleRecord = processModuleInfo(jobFile);
        resultModuleRecords.push_back(newModuleRecord);
    }
    result.moduleRecords = resultModuleRecords;

    jobFile.close();
    return result;
}

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

std::string stripDataLabel(std::string line, bool shift)
{
    auto colonIndex = line.find(": ");
    auto offset = shift ? static_cast<std::string::size_type>(2)
                        : static_cast<std::string::size_type>(1);
    return line.substr(colonIndex + offset);
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

ModuleRecord processModuleInfo(std::ifstream& streamIn)
{
    ModuleRecord result;
    std::string line;
    result.moduleType = chompLine(streamIn, true);
    getline(streamIn, line);
    result.parameters = processParameterInfo(streamIn);
    result.dependencies = processDependencyInfo(streamIn);
    return result;
}

std::vector<std::pair<std::string, std::string>> 
processParameterInfo(std::ifstream& streamIn)
{
    std::vector<std::pair<std::string, std::string>> result;
    std::string line;
    while (getline(streamIn, line) && line != "Dependent ModIns:") {
        std::vector<std::string> data = split(line, ':');
        data[1] = data[1].substr(static_cast<std::string::size_type>(1));
        result.push_back({data[0], data[1]});
    }
    return result;
}

std::vector<std::pair<std::pair<std::string, int>, int>>
processDependencyInfo(std::ifstream& streamIn)
{
    std::vector<std::pair<std::pair<std::string, int>, int>> result;
    std::string line;
    while (getline(streamIn, line) && line != "Module:") {
        std::string parameterName;
        int parameterId;
        int modulatorId;
        std::vector<std::string> linePieces = split(line, ':');
        parameterName = linePieces[0];
        linePieces = split(linePieces[1], ';');
        parameterId = std::stoi(linePieces[0].substr(
                      static_cast<std::string::size_type>(1)));
        modulatorId = std::stoi(linePieces[1].substr(
                      static_cast<std::string::size_type>(1)));
        std::pair<std::string, int> dependencyInitialPart
            {parameterName, parameterId};
       result.push_back({dependencyInitialPart, modulatorId});
    }
    return result;
}
