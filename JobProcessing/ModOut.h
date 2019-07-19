#ifndef MODOUT_H
#define MODOUT_H

#include <vector>

#include "SampleValue.h"

class Module;

class ModOut {
public:
    bool isComputed;
    Module& parentModule;
    Algorithm algorithm;
    std::vector<SampleValue> samples;

    void computeNextSample(void);
};

#endif
