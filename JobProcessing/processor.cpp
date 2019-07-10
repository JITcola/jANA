/* DON'T FORGET TO CLEAR MPFR CACHE AND CLEAR MPFR OBJECTS AT THE END! */

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <map>

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
    bool isMultiprecision;
    int multiprecisionBits;
    long int sampleRate;
    long int length;
    std::vector<int> externalModOutDependencies;
    std::vector<int> externalModInDependencies;
    
    std::map<int,std::vector<double>> modIoMapDouble;
    std::map<int, std::vector<mpfr_t>> modIoMapMulti;

    std::ifstream jobFile {"Job" + std::to_string(jobId) + ".job"};
    
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    id = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    isMultiprecision = data == " double" ? false : true;
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    multiprecisionBits = std::stoi(data);
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    sampleRate = static_cast<long int>(std::stoi(data));
    getline(jobFile, currentLine);
    data = stripDataLabel(currentLine);
    length = static_cast<long int>(std::stoi(data));
    const long int numSamples = length * sampleRate;
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
              << isMultiprecision << "\n"
              << multiprecisionBits << "\n"
              << sampleRate << "\n"
              << length << "\n";
    for (int modId: externalModOutDependencies)
        std::cout << modId << " ";
    std::cout << "\n";
    for (int modId: externalModInDependencies)
        std::cout << modId << " ";
    std::cout << "\n";
    
    std::vector<double> doubleVec;
    std::vector<mpfr_t> mpfrVec;
    std::cout << "doubleVec max size: " << doubleVec.max_size() << "\n"
              << "mpfrVec max size: " << mpfrVec.max_size() << "\n";
              
    /* mpfr_free_cache (); IF MPFR IS USED? */
}

std::string stripDataLabel(std::string line)
{
    return line.substr(line.find(": ") + static_cast<std::string::size_type>(1));
}

enum class Function { sine, saw, square, };

class Module {
public:
    virtual void computeSample(long int sampleIndex);
};

class FunctionGenerator_Double : Module {
public:
    
    double baseFrequency;
    Function function;
    double initPhase;
    double initLevel;
    
    std::vector<double> *frequency = NULL;
    std::vector<double> *phase = NULL;
    std::vector<double> *level = NULL;
    
    std::vector<double> *mainOut = NULL;
    std::vector<double> *auxOut1 = NULL;
    std::vector<double> *auxOut2 = NULL;
    std::vector<double> *auxOut3 = NULL;
    std::vector<double> *auxOut4 = NULL;
    
    FunctionGenerator_Double(long int numSamples, Function function, std::string baseFrequency, std::string initPhase, std::string initLevel) 
    {
        mainOut = new std::vector<double>(numSamples);
        
        switch(function) {
            default: auxOut1 = auxOut2 = auxOut3 = auxOut4 = mainOut;
                     break;
    }
    
    this->baseFrequency = std::stod(baseFrequency);
    this->initPhase = std::stod(initPhase);
    this->initLevel = std::stod(initLevel);
    
    }
    
    ~FunctionGenerator_Double()
    {
        switch(function) {
            default: delete mainOut;
                     break;
        }
    }
    
};

class FunctionGenerator_Multi : Module {
public:
    
    mpfr_t baseFrequency;
    Function function;
    mpfr_t initPhase;
    mpfr_t initLevel;
    
    std::vector<mpfr_t> *frequency = NULL;
    std::vector<mpfr_t> *phase = NULL;
    std::vector<mpfr_t> *level = NULL;
    
    std::vector<mpfr_t> *mainOut = NULL;
    std::vector<mpfr_t> *auxOut1 = NULL;
    std::vector<mpfr_t> *auxOut2 = NULL;
    std::vector<mpfr_t> *auxOut3 = NULL;
    std::vector<mpfr_t> *auxOut4 = NULL;
    
    FunctionGenerator_Multi(long int numSamples, Function function, int precision, std::string baseFrequency, std::string initPhase, std::string initLevel)
    {
        mainOut = new std::vector<mpfr_t>(numSamples);
        for (long int i = 0; i < numSamples; ++i) {
            mpfr_t newNum;
            mpfr_init2 (newNum, static_cast<mpfr_prec_t>(precision));
            mainOut->push_back(newNum);
        }
        
        switch(function) {
            default: auxOut1 = auxOut2 = auxOut3 = auxOut4 = mainOut;
                     break;
        }
        
        mpfr_inits2 (static_cast<mpfr_prec_t>(precision), this->baseFrequency, this->initPhase, this->initLevel, (mpfr_ptr) 0);
        mpfr_set_str (this->baseFrequency, baseFrequency.c_str(), 10, MPFR_RNDN);
        mpfr_set_str (this->initPhase, initPhase.c_str(), 10, MPFR_RNDN);
        mpfr_set_str (this->initLevel, initLevel.c_str(), 10, MPFR_RNDN);
        
    }

    ~FunctionGenerator_Multi()
    {
        for (long int i = 0; i < mainOut->size(); ++i)
            mpfr_clear ((*mainOut)[i]);
        switch(function) {
            default: delete mainOut;
                     break;
        }
        
        mpfr_clears (this->baseFrequency, this->initPhase, this->initLevel, (mpfr_ptr) 0);
    }
};
        

class Delay_Double : Module {
public:
    
    double initTime;
    double initFeedback;
    double initLevel;
    
    std::vector<double> *input = NULL;
    std::vector<double> *time = NULL;
    std::vector<double> *feedback = NULL;
    std::vector<double> *level = NULL;
    
    std::vector<double> *mainOut = NULL;
    
    Delay_Double(long int numSamples, std::string initTime, std::string initFeedback, std::string initLevel)
    {
        mainOut = new std::vector<double>(numSamples);
        
        this->initTime = std::stod(initTime);
        this->initFeedback = std::stod(initFeedback);
        this->initLevel = std::stod(initLevel);
    }
    
    ~Delay_Double()
    {
        delete mainOut;
    }
};

class Delay_Multi : Module {
public:
    
    mpfr_t initTime;
    mpfr_t initFeedback;
    mpfr_t initLevel;
    
    std::vector<mpfr_t> *input = NULL;
    std::vector<mpfr_t> *time = NULL;
    std::vector<mpfr_t> *feedback = NULL;
    std::vector<mpfr_t> *level = NULL;
    
    std::vector<mpfr_t> *mainOut = NULL;
};
    
