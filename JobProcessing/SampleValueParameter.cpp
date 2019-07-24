#include "SampleValueParameter.h"

#include <string>
#include <sstream>
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
        std::ostringstream os;
        os.precision(20);
        os << value.doubleValue;
        std::string valueString {os.str()};
        return valueString;
    }
}
