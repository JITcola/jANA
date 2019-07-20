#include "EvaluatorTemplate.h"

#include <vector>
#include <map>
#include <iostream>
#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

#include "ModOut.h"

Evaluator EvaluatorTemplate::createEvaluator(void)
{
    Evaluator result;
    result.isMultiprecision = jobInfo.precision == "double" ? false : true;
    result.multiprecisionBits = jobInfo.multiprecisionBits;
    result.currentSample = static_cast<long int>(0);
    
    /* Initialize time vector. */
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

    /* Create modulation map. */
    std::map<int, ModIn> modInIdMap;
    std::map<int, ModOut> modOutIdMap;
    std::map<int, int> modInToModOutMap;

    /* Import ModOut dependencies. */
    std::vector<ModOut> modOutDependencies;
    for (int id: jobInfo.modOutDependencyIds) {
        modOutDependencies.push_back(modOutFromId(id));
        modOutIdMap.insert({id, modOutDependencies.back()});
    }

    return result;
}

ModOut EvaluatorTemplate::modOutFromId(int id)
{
    return ModOut {};
}
