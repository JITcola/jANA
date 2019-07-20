#ifndef MODULE_H
#define MODULE_H

#include <vector>

#include "ModIn.h"
#include "ModOut.h"
#include "SampleValue.h"
#include "ModuleRecord.h"

class Evaluator;

class Module {
public:
    bool isMultiprecision;
    int multiprecisionBits;
    std::vector<SampleValue>& time;
    std::vector<ModIn> modIns;
    std::vector<ModOut> modOuts;

    virtual void computeNextSample(void) = 0;

    Module(bool isMultiprecision, int multiprecisionBits,
           std::vector<SampleValue>& time, ModuleRecord& moduleRecord)
        : isMultiprecision {isMultiprecision}, 
          multiprecisionBits {multiprecisionBits},
          time {time}
    {}
};

#endif
