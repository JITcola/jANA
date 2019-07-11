#ifndef MODOUT_H
#define MODOUT_H

#include <vector>

#include "Module.h"
#include "SampleValue.h"

class ModOut {
public:
    bool isComputed;
    Module parentModule;
    std::vector<SampleValue> samples;

    void computeNextSample(void);
};

#endif
