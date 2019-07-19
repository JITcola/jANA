#include "Evaluator.h"

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

void Evaluator::evaluate(void)
{
    for (SampleValue currentSample: time)
        computeNextSample(currentSample);
}

void Evaluator::computeNextSample(SampleValue currentSample)
{
    for (Module* modulePtr: modulePtrs)
        modulePtr->computeNextSample(currentSample);
}

void Evaluator::freeResources(void)
{
    mpfr_free_cache ();
}
