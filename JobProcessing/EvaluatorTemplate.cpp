#include "EvaluatorTemplate.h"

#include <iostream>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

Evaluator EvaluatorTemplate::createEvaluator(void)
{
    Evaluator result;
    result.currentSample = static_cast<long int>(0);
    if (jobInfo.precision == "double")
        for (long int i = 0; i < jobInfo.numberOfSamples; ++i) {
            double time = static_cast<double>(i) / 
                          static_cast<double>(jobInfo.sampleRate);
            result.time.push_back(SampleValue(time));
        }
    else {
        for (long int i = 0; i < jobInfo.numberOfSamples; ++i)
            result.time.push_back(SampleValue(true, jobInfo.multiprecisionBits)); 
        mpfr_t sampleNumber;
        mpfr_t sampleRate;
        mpfr_init2 (sampleNumber, 
                    static_cast<mpfr_prec_t>(jobInfo.multiprecisionBits));
        mpfr_init2 (sampleRate, 
                    static_cast<mpfr_prec_t>(jobInfo.multiprecisionBits));
        mpfr_set_si (sampleRate, 
                     static_cast<long int>(jobInfo.sampleRate),
                     MPFR_RNDN);
        for (long int i = 0; i < jobInfo.numberOfSamples; ++i) {
            mpfr_set_si (sampleNumber, i, MPFR_RNDN);
            mpfr_div (result.time[i].multiValue, sampleNumber, sampleRate, 
                      MPFR_RNDN);
        }
        mpfr_clear (sampleNumber);
        mpfr_clear (sampleRate);
    }
    return result;
}


