#ifndef SAMPLEVALUE_H
#define SAMPLEVALUE_H

#include <string>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

class SampleValue {
public:
    bool isMultiprecision;
    union {
        double doubleValue;
        mpfr_t multiValue;
    };
    SampleValue();
    SampleValue(double doubleValue);
    SampleValue(bool isMultiprecision, int precision);
    SampleValue(bool isMultiprecision, int precision, std::string valueString);
    ~SampleValue();
};

#endif
