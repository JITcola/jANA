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

std::string stripDataLabel(std::string line)
{
    return line.substr(line.find(": ") + static_cast<std::string::size_type>(1));
}

enum class Function { sine, saw, square, invalid, };

Function functionStringToFunction(std::string input)
{
    if (input == "sine")
        return Function::sine;
    else if (input == "saw")
        return Function::saw;
    else if (input == "square")
        return Function::square;
    else
        return Function::invalid;
}

class DoubleModule {
public:
    virtual void computeSample(long int sampleIndex) = 0;
    virtual double *modInNameToArray(std::string modInName) = 0;
    virtual double *modOutNameToArray(std::string modOutName) = 0;
};

class MultiModule {
public:
    virtual void computeSample(long int sampleIndex) = 0;
    virtual mpfr_t *modInNameToArray(std::string modInName) = 0;
    virtual mpfr_t *modOutNameToArray(std::string modOutName) = 0;
};

class FunctionGenerator_Double : public DoubleModule {
public:
    
    long int numSamples;
    
    double baseFrequency;
    Function function;
    double initPhase;
    double initLevel;
    
    double *frequency = NULL;
    double *phase = NULL;
    double *level = NULL;
    
    double *mainOut = NULL;
    double *auxOut1 = NULL;
    double *auxOut2 = NULL;
    double *auxOut3 = NULL;
    double *auxOut4 = NULL;
    
    FunctionGenerator_Double(long int numSamples, Function function, std::string baseFrequency, std::string initPhase, std::string initLevel) 
    {
        this->numSamples = numSamples;
        
        mainOut = new double[this->numSamples];
        
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
            default: delete[] mainOut;
                     break;
        }
    }
    
    double *modInNameToArray(std::string modInName)
    {
        if (modInName == "frequency")
            return frequency;
        else if (modInName == "phase")
            return phase;
        else if (modInName == "level")
            return level;
        else
            return NULL;
    }
    
    double *modOutNameToArray(std::string modOutName)
    {
        if (modOutName == "mainOut")
            return mainOut;
        else if (modOutName == "auxOut1")
            return auxOut1;
        else if (modOutName == "auxOut2")
            return auxOut2;
        else if (modOutName == "auxOut3")
            return auxOut3;
        else if (modOutName == "auxOut4")
            return auxOut4;
        else
            return NULL;
    }
    
    void computeSample(long int sampleIndex)
    {
        return;
    }
    
};

class FunctionGenerator_Multi : public MultiModule {
public:
    
    long int numSamples;
    
    mpfr_t baseFrequency;
    Function function;
    mpfr_t initPhase;
    mpfr_t initLevel;
    
    mpfr_t *frequency;
    mpfr_t *phase;
    mpfr_t *level;
    
    mpfr_t *mainOut;
    mpfr_t *auxOut1;
    mpfr_t *auxOut2;
    mpfr_t *auxOut3;
    mpfr_t *auxOut4;
    
    FunctionGenerator_Multi(long int numSamples, Function function, std::string baseFrequency, std::string initPhase, std::string initLevel, int precision)
    {
        this->numSamples = numSamples;
        
        mainOut = new mpfr_t[this->numSamples];
        
        for (long int i = 0; i < numSamples; ++i)
            mpfr_init2 (mainOut[i], static_cast<mpfr_prec_t>(precision));
            
        
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
        for (long int i = 0; i < numSamples; ++i)
            mpfr_clear (mainOut[i]);
        switch(function) {
            default: delete[] mainOut;
                     break;
        }
        
        mpfr_clears (baseFrequency, initPhase, initLevel, (mpfr_ptr) 0);
    }
    
    mpfr_t *modInNameToArray(std::string modInName)
    {
        if (modInName == "frequency")
            return frequency;
        else if (modInName == "phase")
            return phase;
        else if (modInName == "level")
            return level;
        else
            return NULL;
    }
    
    mpfr_t *modOutNameToArray(std::string modOutName)
    {
        if (modOutName == "mainOut")
            return mainOut;
        else if (modOutName == "auxOut1")
            return auxOut1;
        else if (modOutName == "auxOut2")
            return auxOut2;
        else if (modOutName == "auxOut3")
            return auxOut3;
        else if (modOutName == "auxOut4")
            return auxOut4;
        else
            return NULL;
    }
    
    void computeSample(long int sampleIndex)
    {
        return;
    }
    
};

class Delay_Double : public DoubleModule {
public:
    
    long int numSamples;
    
    double initTime;
    double initFeedback;
    double initLevel;
    
    double *input = NULL;
    double *time = NULL;
    double *feedback = NULL;
    double *level = NULL;
    
    double *mainOut = NULL;
    
    Delay_Double(long int numSamples, std::string initTime, std::string initFeedback, std::string initLevel)
    {
        this->numSamples = numSamples;
        
        mainOut = new double[this->numSamples];
        
        this->initTime = std::stod(initTime);
        this->initFeedback = std::stod(initFeedback);
        this->initLevel = std::stod(initLevel);
    }
    
    ~Delay_Double()
    {
        delete[] mainOut;
    }
    
    double *modInNameToArray(std::string modInName)
    {
        if (modInName == "input")
            return input;
        else if (modInName == "time")
            return time;
        else if (modInName == "feedback")
            return feedback;
        else if (modInName == "level")
            return level;
        else
            return NULL;
    }
    
    double *modOutNameToArray(std::string modOutName)
    {
        if (modOutName == "mainOut")
            return mainOut;
        else
            return NULL;
    }
    
    void computeSample(long int sampleIndex)
    {
        return;
    }
};

class Delay_Multi : public MultiModule {
public:
    
    long int numSamples;
    
    mpfr_t initTime;
    mpfr_t initFeedback;
    mpfr_t initLevel;
    
    mpfr_t *input = NULL;
    mpfr_t *time = NULL;
    mpfr_t *feedback = NULL;
    mpfr_t *level = NULL;
    
    mpfr_t *mainOut = NULL;
    
    Delay_Multi(long int numSamples, std::string initTime, std::string initFeedback, std::string initLevel, int precision)
    {
        this->numSamples = numSamples;
        
        mainOut = new mpfr_t[this->numSamples];
        for (long int i = 0; i < numSamples; ++i)
            mpfr_init2 (mainOut[i], static_cast<mpfr_prec_t>(precision));
                    
        mpfr_inits2 (static_cast<mpfr_prec_t>(precision), this->initTime, this->initFeedback, this->initLevel, (mpfr_ptr) 0);
        mpfr_set_str (this->initTime, initTime.c_str(), 10, MPFR_RNDN);
        mpfr_set_str (this->initFeedback, initFeedback.c_str(), 10, MPFR_RNDN);
        mpfr_set_str (this->initLevel, initLevel.c_str(), 10, MPFR_RNDN);
        
    }
    
    ~Delay_Multi()
    {
        for (long int i = 0; i < numSamples; ++i)
            mpfr_clear (mainOut[i]);
        
        delete[] mainOut;
        
        mpfr_clears (initTime, initFeedback, initLevel, (mpfr_ptr) 0);
    }
    
    mpfr_t *modInNameToArray(std::string modInName)
    {
        if (modInName == "input")
            return input;
        else if (modInName == "time")
            return time;
        else if (modInName == "feedback")
            return feedback;
        else if (modInName == "level")
            return level;
        else
            return NULL;
    }
    
    mpfr_t *modOutNameToArray(std::string modOutName)
    {
        if (modOutName == "mainOut")
            return mainOut;
        else
            return NULL;
    }
    
    void computeSample(long int sampleIndex)
    {
        return;
    }
    
};

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
    
    
    std::vector<DoubleModule *> moduleVectorDouble;
    std::vector<MultiModule *> moduleVectorMulti;
    std::map<int,double *> modInArrayMapDouble;
    std::map<int, mpfr_t *> modInArrayMapMulti;
    std::map<int, double *> modOutArrayMapDouble;
    std::map<int, mpfr_t *> modOutArrayMapMulti;
    std::map<int, int> modConnectionMap; // Note that the keys are always ModInIds and the values are always ModOutIds

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
    getline(jobFile,currentLine);
    while(getline(jobFile, currentLine)) {
        data = stripDataLabel(currentLine);
        data = data.substr(static_cast<std::string::size_type>(1));
        if (data == "FunctionGenerator") {
            getline(jobFile, currentLine);
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string baseFrequency = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            Function function = functionStringToFunction(data.substr(static_cast<std::string::size_type>(1)));
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string initPhase = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string initLevel = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            if (isMultiprecision) {
                FunctionGenerator_Multi *newFG = new FunctionGenerator_Multi(numSamples, function, baseFrequency, initPhase, initLevel, multiprecisionBits);
                moduleVectorMulti.push_back(newFG);
                while (getline(jobFile, currentLine), currentLine != "Dependency ModOuts:") {
                    std::string modInName;
                    int modInId;
                    int modOutId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modInName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modInId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                           semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modOutId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modInArrayMapMulti.insert({modInId, moduleVectorMulti.back()->modInNameToArray(modInName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
                while (getline(jobFile, currentLine) && currentLine != "Module:") {
                    std::string modOutName;
                    int modOutId;
                    int modInId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modOutName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modOutId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                            semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modInId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modOutArrayMapMulti.insert({modOutId, moduleVectorMulti.back()->modOutNameToArray(modOutName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
            } else {
                FunctionGenerator_Double *newFG = new FunctionGenerator_Double(numSamples, function, baseFrequency, initPhase, initLevel);
                moduleVectorDouble.push_back(newFG);
                while (getline(jobFile, currentLine), currentLine != "Dependency ModOuts:") {
                    std::string modInName;
                    int modInId;
                    int modOutId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modInName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modInId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                           semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modOutId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modInArrayMapDouble.insert({modInId, moduleVectorDouble.back()->modInNameToArray(modInName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
                while (getline(jobFile, currentLine) && currentLine != "Module:") {
                    std::string modOutName;
                    int modOutId;
                    int modInId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modOutName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modOutId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                            semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modInId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modOutArrayMapDouble.insert({modOutId, moduleVectorDouble.back()->modOutNameToArray(modOutName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
            }
        }
        if (data == "Delay") {
            getline(jobFile, currentLine);
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string initTime = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string initFeedback = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            data = stripDataLabel(currentLine);
            std::string initLevel = data.substr(static_cast<std::string::size_type>(1));
            getline(jobFile, currentLine);
            if (isMultiprecision) {
                Delay_Multi *newDelay = new Delay_Multi(numSamples, initTime, initFeedback, initLevel, multiprecisionBits);
                moduleVectorMulti.push_back(newDelay);
                while (getline(jobFile, currentLine), currentLine != "Dependency ModOuts:") {
                    std::string modInName;
                    int modInId;
                    int modOutId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modInName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modInId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                           semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modOutId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modInArrayMapMulti.insert({modInId, moduleVectorMulti.back()->modInNameToArray(modInName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
                while (getline(jobFile, currentLine) && currentLine != "Module:") {
                    std::string modOutName;
                    int modOutId;
                    int modInId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modOutName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modOutId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                            semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modInId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modOutArrayMapMulti.insert({modOutId, moduleVectorMulti.back()->modOutNameToArray(modOutName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
            } else {
                Delay_Double *newDelay = new Delay_Double(numSamples, initTime, initFeedback, initLevel);
                moduleVectorDouble.push_back(newDelay);
                while (getline(jobFile, currentLine), currentLine != "Dependency ModOuts:") {
                    std::string modInName;
                    int modInId;
                    int modOutId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modInName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modInId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                           semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modOutId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modInArrayMapDouble.insert({modInId, moduleVectorDouble.back()->modInNameToArray(modInName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
                while (getline(jobFile, currentLine) && currentLine != "Module:") {
                    std::string modOutName;
                    int modOutId;
                    int modInId;
                    std::string::size_type colonIndex;
                    std::string::size_type semicolonIndex;
                    colonIndex = currentLine.find(':');
                    semicolonIndex = currentLine.find(';');
                    modOutName = currentLine.substr(static_cast<std::string::size_type>(0), colonIndex);
                    modOutId = std::stoi(currentLine.substr(colonIndex + static_cast<std::string::size_type>(2),
                                                            semicolonIndex - colonIndex - static_cast<std::string::size_type>(2)));
                    modInId = std::stoi(currentLine.substr(semicolonIndex + static_cast<std::string::size_type>(2)));
                    modOutArrayMapDouble.insert({modOutId, moduleVectorDouble.back()->modOutNameToArray(modOutName)});
                    modConnectionMap.insert({modInId, modOutId});
                }
            }
        }
    }
              
    mpfr_free_cache ();
}

int main(void)
{
    processJob(5);
    return 0;
}
