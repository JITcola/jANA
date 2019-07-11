#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>

#include <Module.h>
#include <SampleValue.h>

class Evaluator {
public:
    std::vector<Module> modules;
    long int currentSample;
    std::vector<SampleValue> time;

    void evaluate(void);
    void computeNextSample(void);
    void freeResources(void);
};

#endif
