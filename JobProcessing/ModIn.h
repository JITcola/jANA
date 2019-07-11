#ifndef MODIN_H
#define MODIN_H

#include "ModOut.h"
#include "SampleValue.h"

class ModIn {
public:
    ModOut source;
    
    SampleValue getSampleValue(long int sampleNumber);
};

#endif
