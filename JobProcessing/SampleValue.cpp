#include "SampleValue.h"

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

SampleValue::SampleValue()
{
    isMultiprecision = false;
}

SampleValue::SampleValue(double doubleValue)
{
    isMultiprecision = false;
    this->doubleValue = doubleValue;
}

SampleValue::SampleValue(bool isMultiprecision, int precision)
{
    this->isMultiprecision = isMultiprecision;
    if (this->isMultiprecision)
        mpfr_init2 (multiValue, static_cast<mpfr_prec_t>(precision));
}

SampleValue::SampleValue(bool isMultiprecision, int precision, std::string valueString)
{
    this->isMultiprecision = isMultiprecision;
    if (this->isMultiprecision) {
        mpfr_init2 (multiValue, static_cast<mpfr_prec_t>(precision));
        mpfr_set_str (multiValue, valueString.c_str(), 10, MPFR_RNDN);
    }
}

SampleValue::~SampleValue()
{
    if (isMultiprecision)
        mpfr_clear (multiValue);
}
