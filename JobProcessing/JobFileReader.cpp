#include "JobFileReader.h"

#include <string>
#include <vector>
#include <fstream>
#include <utility>

#include "StringUtils.h"

using namespace StringUtils;

ModuleRecord processModuleInfo(std::ifstream& streamIn);
std::vector<std::pair<std::string, std::string>> 
    processParameterInfo(std::ifstream& streamIn);
std::vector<std::pair<std::pair<std::string, int>, int>>
    processDependencyInfo(std::ifstream& streamIn);
std::vector<std::pair<std::string, int>>
    processProductInfo(std::ifstream& streamIn);

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
    while(jobFile)
        resultModuleRecords.push_back(processModuleInfo(jobFile));
    result.moduleRecords = resultModuleRecords;

    jobFile.close();
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
    result.products = processProductInfo(streamIn);
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
    while (getline(streamIn, line) && line != "Computed ModOuts:") {
        std::string modInName;
        int modInId;
        int modulatorId;
        std::vector<std::string> linePieces = split(line, ':');
        modInName = linePieces[0];
        linePieces = split(linePieces[1], ';');
        modInId = std::stoi(linePieces[0].substr(
                      static_cast<std::string::size_type>(1)));
        modulatorId = std::stoi(linePieces[1].substr(
                      static_cast<std::string::size_type>(1)));
        std::pair<std::string, int> dependencyInitialPart
            {modInName, modInId};
       result.push_back({dependencyInitialPart, modulatorId});
    }
    return result;
}

std::vector<std::pair<std::string, int>>
processProductInfo(std::ifstream& streamIn)
{
    std::vector<std::pair<std::string, int>> result;
    std::string line;
    while (getline(streamIn, line) && line != "Module:") {
        std::string modOutName;
        int modOutId;
        std::vector<std::string> linePieces = split(line, ':');
        modOutName = linePieces[0];
        modOutId = std::stoi(linePieces[1].substr(
                   static_cast<std::string::size_type>(1)));
        result.push_back({modOutName, modOutId});
    }
    return result;
}
