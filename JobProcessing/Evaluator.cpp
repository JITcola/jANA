#include "Evaluator.h"

#include <memory>
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
    for (std::unique_ptr<Module>& modulePtr: modulePtrs)
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
