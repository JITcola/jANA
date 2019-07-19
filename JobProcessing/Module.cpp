#include <utility>

#include "Module.h"
#include "Evaluator.h"
#include "ModuleRecord.h"

Module::Module(Evaluator& parentEvaluator, ModuleRecord& moduleRecord)
{
    this.parentEvaluator = parentEvaluator;
    for (std::pair<std::string, std::string> parameterRecord: moduleRecord.parameters) {
        Parameter newParameter {parameterRecord.first, parameterRecord.second,
                               bool isMultiprecision, int precision};
        parameters.push_back(newParameter);
    }
}

