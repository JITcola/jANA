#include "SampleValueParameter.h"

#include <string>
#include "SampleValue.h"

SampleValueParameter::SampleValueParameter()
    : Parameter()
{
    SampleValue newSampleValue;
    value = newSampleValue;
}

SampleValueParameter::SampleValueParameter(std::string name, 
                                           double doubleValue)
    : Parameter(name)
{
    SampleValue parameterValue {doubleValue};
    value = parameterValue;
}

SampleValueParameter::SampleValueParameter(std::string name, 
                                           bool isMultiprecision,
                                           int precision)
    : Parameter(name)
{
    SampleValue parameterValue {isMultiprecision, precision};
    value = parameterValue;
}

SampleValueParameter::SampleValueParameter(std::string name, 
                                           bool isMultiprecision,
                                           int precision, 
                                           std::string valueString)
    : Parameter(name)
{
    SampleValue parameterValue {isMultiprecision, precision, valueString};
    value = parameterValue;
}

