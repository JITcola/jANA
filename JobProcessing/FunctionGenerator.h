#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H

#include "Module.h"
#include "ModuleRecord.h"

class FunctionGenerator : public Module {
public:
    void computeNextSample(SampleValue currentSample);
    FunctionGenerator(ModuleRecord record);
};
