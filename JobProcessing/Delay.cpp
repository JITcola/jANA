#include "Delay.h"

#include <iostream>

void Delay::computeNextSample()
{
    return;
}

Delay::Delay(bool isMultiprecision, int multiprecisionBits,
             std::vector<SampleValue>& time, ModuleRecord& moduleRecord)
    : Module(isMultiprecision, multiprecisionBits, time)
{
    for (auto parameter: moduleRecord.parameters) {
        if (parameter.first == "initTime") {
            if (isMultiprecision) {
                SampleValueParameter newParameter {"initTime",
                                                   isMultiprecision,
                                                   multiprecisionBits,
                                                   parameter.second};
                initTime = newParameter;
            } else {
                SampleValueParameter newParameter {"initTime",
                                                   std::stod(parameter.second)};
                initTime = newParameter;
            }
        } else if (parameter.first == "initFeedback") {
            if (isMultiprecision) {
                SampleValueParameter newParameter {"initFeedback",
                                                   isMultiprecision,
                                                   multiprecisionBits,
                                                   parameter.second};
                initFeedback = newParameter;
            } else {
                SampleValueParameter newParameter {"initFeedback",
                                                   std::stod(parameter.second)};
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
            }
        } else
            std::cerr << "Invalid input to Delay constructor." << std::endl;
    }
}
