#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

void processJob(int jobId);

std::string stripDataLabel(std::string line);

int main(void)
{
    processJob(5);
    return 0;
}

void processJob(int jobId)
{
    std::string currentLine;
    std::string standardSeparator{": "};
    std::string::size_type index;
    std::string data;
    int id {jobId};
    bool doublePrecision;
    int multiprecisionBits;
    int sampleRate;
    int length;
    std::vector<int> externalModOutDependencies;
    std::vector<int> externalModInDependencies;

    std::ifstream jobFile {"Job" + std::to_string(jobId) + ".job"};
    
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    id = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    doublePrecision = data == " double" ? true : false;
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    multiprecisionBits = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    sampleRate = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    length = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    if (data != " ") {
        if (data.find(',') == std::string::npos) {
            externalModOutDependencies.push_back(stoi(data));
        } else {
            std::string::size_type nextCommaIndex = data.find(',');
            while (nextCommaIndex != std::string::npos) {
                externalModOutDependencies.push_back(stoi(data.substr(static_cast<std::string::size_type>(0), nextCommaIndex)));
                data = data.substr(nextCommaIndex + static_cast<std::string::size_type>(1));
                nextCommaIndex = data.find(',');
            }
            externalModOutDependencies.push_back(stoi(data));
        }
    }
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    if (data != " ") {
        if (data.find(',') == std::string::npos) {
            externalModInDependencies.push_back(stoi(data));
        } else {
            std::string::size_type nextCommaIndex = data.find(',');
            while (nextCommaIndex != std::string::npos) {
                externalModInDependencies.push_back(stoi(data.substr(static_cast<std::string::size_type>(0), nextCommaIndex)));
                data = data.substr(nextCommaIndex + static_cast<std::string::size_type>(1));
                nextCommaIndex = data.find(',');
            }
            externalModInDependencies.push_back(stoi(data));
        }
    }
            
    std::cout << id << "\n"
              << doublePrecision << "\n"
              << multiprecisionBits << "\n"
              << sampleRate << "\n"
              << length << "\n";
    for (int modId: externalModOutDependencies)
        std::cout << modId << " ";
    std::cout << "\n";
    for (int modId: externalModInDependencies)
        std::cout << modId << " ";
    std::cout << "\n";
}

std::string stripDataLabel(std::string line)
{
    return line.substr(line.find(": ") + static_cast<std::string::size_type>(1));
}

class FunctionGenerator_Double {
public:
    double baseFrequency;
    int function;
    double initPhase;
    double initLevel;
    std::vector<double> *frequency = NULL;
    std::vector<double> *phase = NULL;
    std::vector<double> *level = NULL;
    std::vector<double> mainOut;
    std::vector<double> auxOut1;
    std::vector<double> auxOut2;
    std::vector<double> auxOut3;
    std::vector<double> auxOut4;
};

class Delay_Double {
public:
    double initTime;
    double initFeedback;
    double initLevel;
    std::vector<double> *input = NULL;
    std::vector<double> *time = NULL;
    std::vector<double> *feedback = NULL;
    std::vector<double> *level = NULL;
    std::vector<double> mainOut;
};
    
