#include "FunctionGenerator.h"

void FunctionGenerator::computeNextSample(SampleValue currentSample)
{
    for (ModOut modOut: modOuts)
        if (modOut.isComputed)
            modOut.computeNextSample(currentSample);
}
