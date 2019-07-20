#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H

#include "Module.h"
#include "ModuleRecord.h"
#include "Evaluator.h"

class FunctionGenerator : public Module {
public:
    void computeNextSample();
    FunctionGenerator(bool isMultiprecision, int multiprecisionBits,
                      std::vector<SampleValue>& time, ModuleRecord& moduleRecord);
};

#endif
