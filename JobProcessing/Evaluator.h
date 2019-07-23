#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <map>
#include <memory>

#include "Module.h"
#include "SampleValue.h"
#include "ModOut.h"
#include "EvaluatorTemplate.h"

class Evaluator {
public:
    bool isMultiprecision;
    int multiprecisionBits;
    std::vector<std::unique_ptr<Module>> modulePtrs;
    long int currentSample;
    std::vector<SampleValue> time;
    std::vector<ModOut> modOutDependencies;

    void evaluate(void);

    Evaluator(EvaluatorTemplate evaluatorTemplate);

private:
    void computeNextSample();
    void freeResources(void);
    void exportModOutProducts(void);

    ModOut modOutFromId(int id);
};

#endif
