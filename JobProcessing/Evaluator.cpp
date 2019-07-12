#include "Evaluator.h"

#include <cstdio>
#include <gmp.h>
#include <mpfr.h>

void Evaluator::freeResources(void)
{
    mpfr_free_cache ();
}
