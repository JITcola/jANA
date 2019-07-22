#include "ModuleRecord.h"

#include <string>
#include <utility>

SampleValueParameter ModuleRecord::getSampleValueParameter(
    std::string parameterName,
    bool isMultiprecision,
    int multiprecisionBits)
{
    std::string parameterValue;
    for (auto parameter: parameters)
        if (parameter.first == parameterName)
            parameterValue = parameter.second;
    if (isMultiprecision)
        return SampleValueParameter {
            parameterName,
            isMultiprecision,
            multiprecisionBits,
            parameterValue};
    else
        return SampleValueParameter {
            parameterName,
            std::stod(parameterValue)};
}
            

OptionParameter ModuleRecord::getOptionParameter(
    std::string parameterName)
{
    std::string parameterValue;
    for (auto parameter: parameters)
        if (parameter.first == parameterName)
            parameterValue = parameter.second;
    return OptionParameter {parameterName, parameterValue};
}

