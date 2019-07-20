#include "Delay.h"

void Delay::computeNextSample()
{
    return;
}

Delay::Delay(bool isMultiprecision, int multiprecisionBits,
             std::vector<SampleValue>& time, ModuleRecord& moduleRecord)
    : Module(isMultiprecision, multiprecisionBits,
             time, moduleRecord)
{

}
