#include "FunctionGenerator.h"

void FunctionGenerator::computeNextSample()
{
    return;
}

FunctionGenerator::FunctionGenerator(bool isMultiprecision, 
                                     int multiprecisionBits,
                                     std::vector<SampleValue>& time,
                                     ModuleRecord& moduleRecord)
    : Module(isMultiprecision, multiprecisionBits, time, moduleRecord)
{

}
    
