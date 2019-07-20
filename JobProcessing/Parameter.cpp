#include "Parameter.h"
#include <string>

Parameter::Parameter(std::string name, std::string valueString,
                     bool isMultiprecision, int precision)
{
    this->name = name;
    this->value = SampleValue {isMultiprecision, precision, valueString};
}
