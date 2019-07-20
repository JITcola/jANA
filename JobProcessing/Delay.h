#ifndef DELAY_H
#define DELAY_H

#include "Module.h"
#include "ModuleRecord.h"

class Delay : public Module {
public:
    void computeNextSample();
    Delay(bool isMultiprecision, int multiprecisionBits,
                      std::vector<SampleValue>& time, ModuleRecord& moduleRecord);
};

#endif
