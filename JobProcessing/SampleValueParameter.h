#ifndef SAMPLEVALUEPARAMETER_H
#define SAMPLEVALUEPARAMETER_H

#include <string>

#include "Parameter.h"
#include "SampleValue.h"

class SampleValueParameter : public Parameter {
public:
    SampleValue value;

    std::string getValueAsString();

    SampleValueParameter() = default;
    SampleValueParameter(const SampleValueParameter& sampleValueParameter)
        : Parameter(sampleValueParameter.name), 
          value {sampleValueParameter.value} {}
    SampleValueParameter(std::string name, double doubleValue)
        : Parameter(name), value {doubleValue} {}
    SampleValueParameter(std::string name, bool isMultiprecision,
                         int precision)
        : Parameter(name),
          value {isMultiprecision, precision} {}
    SampleValueParameter(std::string name, 
                         bool isMultiprecision,
                         int precision, 
                         std::string valueString)
        : Parameter(name),
          value {isMultiprecision, precision, valueString} {}
};

#endif
