#ifndef MODOUT_H
#define MODOUT_H

#include <vector>

#include "SampleValue.h"
#include "Algorithm.h"

class Module;

class ModOut {
public:
    bool isComputed;
    std::vector<SampleValue> samples;

    ModOut() = default;
    ModOut(bool isComputed) : isComputed{isComputed} {}
};

#endif
