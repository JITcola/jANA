#include "Evaluator.h"

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

void Evaluator::evaluate(void)
{
    for (long int i = 0; i < time.size(); ++i)
        computeNextSample();
    freeResources();
    exportModOutProducts();
}

void Evaluator::computeNextSample()
{
    for (Module* modulePtr: modulePtrs)
        modulePtr->computeNextSample();
}

void Evaluator::freeResources(void)
{
    mpfr_free_cache ();
}

void Evaluator::exportModOutProducts(void)
{
    return;
}
