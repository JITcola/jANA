#ifndef MODULE_H
#define MODULE_H

#include <vector>
#include <string>

#include "ModIn.h"
#include "ModOut.h"
#include "SampleValue.h"
#include "ModuleRecord.h"
#include "ModuleType.h"

class Evaluator;

class Module {
public:
    ModuleType moduleType;
    bool isMultiprecision;
    int multiprecisionBits;
    std::vector<SampleValue>& time;

    virtual void computeNextSample(void) = 0;
    virtual ModIn& getModIn(std::string modInName) = 0;
    virtual ModOut& getModOut(std::string modOutName) = 0;
    virtual Parameter& getParameter(std::string parameterName) = 0;
    static ModuleType moduleTypeFromString(std::string moduleTypeString);

    Module(ModuleType moduleType, bool isMultiprecision, 
           int multiprecisionBits, std::vector<SampleValue>& time)
        : moduleType {moduleType},
          isMultiprecision {isMultiprecision}, 
          multiprecisionBits {multiprecisionBits},
          time {time}
    {}
};

#endif
