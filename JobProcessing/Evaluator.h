#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <map>

#include "Module.h"
#include "SampleValue.h"
#include "ModOut.h"

class Evaluator {
public:
    bool isMultiprecision;
    int multiprecisionBits;
    std::vector<Module*> modulePtrs;
    long int currentSample;
    std::vector<SampleValue> time;
    std::map<int, ModOut> modOutDependencyRecords;
    std::map<int, ModOut> modOutProductRecords;

    void evaluate(void);

private:
    void computeNextSample(SampleValue sampleValue);
    void freeResources(void);
};

#endif
