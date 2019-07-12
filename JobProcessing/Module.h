#ifndef MODULE_H
#define MODULE_H

#include <vector>

#include "Parameter.h"
#include "ModIn.h"
#include "ModOut.h"
#include "SampleValue.h"

class Evaluator;

class Module {
public:
    Evaluator& parentEvaluator;
    std::vector<Parameter> parameters;
    std::vector<ModIn> modIns;
    std::vector<ModOut> modOuts;

    void computeNextSample(void);
    SampleValue getParameterValue(std::string parameterName);
};

#endif
    
