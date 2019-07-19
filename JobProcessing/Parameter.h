#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

#include "SampleValue.h"

class Parameter {
public:
    std::string name;
    SampleValue value;
    Parameter(std::string name, std::string valueString,
              bool isMultiprecision, int precision);
};

#endif
