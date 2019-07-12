#include "SampleValue.h"

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

SampleValue::SampleValue()
{
    isMultiprecision = false;
}

SampleValue::SampleValue(const SampleValue& sampleValue)
{
    isMultiprecision = sampleValue.isMultiprecision;
    if (isMultiprecision) {
        multiprecisionBits = sampleValue.multiprecisionBits;
        mpfr_init2 (multiValue, 
                    static_cast<mpfr_prec_t>(multiprecisionBits));
        mpfr_set (multiValue, sampleValue.multiValue, MPFR_RNDN);
    } else
        doubleValue = sampleValue.doubleValue;
}

SampleValue::SampleValue(double doubleValue)
{
    isMultiprecision = false;
    this->doubleValue = doubleValue;
}

SampleValue::SampleValue(bool isMultiprecision, int precision)
    : multiprecisionBits {precision}
{
    this->isMultiprecision = isMultiprecision;
    if (this->isMultiprecision)
        mpfr_init2 (multiValue, 
                    static_cast<mpfr_prec_t>(multiprecisionBits));
}

SampleValue::SampleValue(bool isMultiprecision, int precision, 
                         std::string valueString)
    : multiprecisionBits {precision}
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
