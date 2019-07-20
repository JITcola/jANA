#include <utility>

#include "Module.h"
#include "Evaluator.h"
#include "ModuleRecord.h"

Module::Module(bool isMultiprecision, int multiprecisionBits, 
               std::vector<SampleValue>& time, ModuleRecord& moduleRecord)
    : isMultiprecision{isMultiprecision}, multiprecisionBits{multiprecisionBits}, 
      time{time}
{
    for (std::pair<std::string, std::string> parameterRecord: moduleRecord.parameters) {
        Parameter newParameter {parameterRecord.first, parameterRecord.second,
                                this->isMultiprecision,
                                this->multiprecisionBits};
        parameters.push_back(newParameter);
    }
}

