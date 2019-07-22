#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H

#include "Module.h"
#include "ModuleRecord.h"
#include "SampleValueParameter.h"
#include "OptionParameter.h"

class FunctionGenerator : public Module {
public:
    SampleValueParameter baseFrequency;
    OptionParameter function;
    SampleValueParameter initPhase;
    SampleValueParameter initLevel;

    void computeNextSample();

    FunctionGenerator(bool isMultiprecision, int multiprecisionBits,
                      std::vector<SampleValue>& time, ModuleRecord& moduleRecord);
};

#endif
