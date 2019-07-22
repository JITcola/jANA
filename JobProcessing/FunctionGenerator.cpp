#include "FunctionGenerator.h"

#include <vector>
#include <iostream>

void FunctionGenerator::computeNextSample()
{
    return;
}
/*
FunctionGenerator::FunctionGenerator(bool isMultiprecision, 
                                     int multiprecisionBits,
                                     std::vector<SampleValue>& time,
                                     ModuleRecord& moduleRecord)
    : Module(isMultiprecision, multiprecisionBits, time)
{
    for (auto parameter: moduleRecord.parameters) {
        if (parameter.first == "baseFrequency") {
           if (isMultiprecision) {
              SampleValueParameter newParameter {"baseFrequency", 
                                                 isMultiprecision,
                                                 multiprecisionBits,
                                                 parameter.second};
              baseFrequency = newParameter;
           } else {
              SampleValueParameter newParameter {"baseFrequency",
                                                 std::stod(parameter.second)};
              baseFrequency = newParameter;
           }
        } else if (parameter.first == "function") {
            OptionParameter newParameter {"function", parameter.second};
            function = newParameter;
        } else if (parameter.first == "initPhase") {
            if (isMultiprecision) {
                SampleValueParameter newParameter {"initPhase",
                                                   isMultiprecision,
                                                   multiprecisionBits,
                                                   parameter.second};
                initPhase = newParameter;
            } else {
                SampleValueParameter newParameter {"initPhase",
                                                   std::stod(parameter.second)};
                initPhase = newParameter;
            }
        } else if (parameter.first == "initLevel") {
            if (isMultiprecision) {
                SampleValueParameter newParameter {"initLevel",
                                                   isMultiprecision,
                                                   multiprecisionBits,
                                                   parameter.second};
                initLevel = newParameter;
            } else {
                SampleValueParameter newParameter {"initLevel",
                                                   std::stod(parameter.second)};
                initLevel = newParameter;
            }
        } else
            std::cerr << "Invalid input to FunctionGenerator constructor." << std::endl;
    }
}
*/
