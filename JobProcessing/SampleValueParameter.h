#ifndef SAMPLEVALUEPARAMETER_H
#define SAMPLEVALUEPARAMETER_H

#include <string>

#include "Parameter.h"
#include "SampleValue.h"

class SampleValueParameter : public Parameter {
public:
    SampleValue value;

    SampleValueParameter();
    SampleValueParameter(const SampleValueParameter& sampleValueParameter)
        : value {sampleValueParameter.value} {}
    SampleValueParameter(std::string name, double doubleValue);
    SampleValueParameter(std::string name, bool isMultiprecision,
                         int precision);
    SampleValueParameter(std::string name, 
                         bool isMultiprecision,
                         int precision, 
                         std::string valueString);
};

#endif
