#include "SampleValueParameter.h"

#include <string>
#include <gmp.h>
#include <mpfr.h>

std::string SampleValueParameter::getValueAsString()
{
    if (value.isMultiprecision) {
        char* str;
        mpfr_asprintf (&str, "%Re", value.multiValue);
        std::string valueString {str};
        mpfr_free_str (str);
        return valueString;
    } else {
        std::string valueString {std::to_string(value.doubleValue)};
        return valueString;
    }
}
