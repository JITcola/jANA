#ifndef MODOUT_H
#define MODOUT_H

#include <vector>
#include <string>

#include "SampleValue.h"
#include "Algorithm.h"
#include "DatFileReader.h"

class Module;

class ModOut {
public:
    std::string name;
    bool isComputed;
    std::vector<SampleValue> samples;

    ModOut()
        : name {"Unnamed ModOut"}, isComputed {false} {}
    ModOut(std::string name)
        : name {name}, isComputed {false} {}
    ModOut(std::string name, bool isComputed) 
        : name {name}, isComputed {isComputed} {}

    void samplesFromDat(const DatFileReader& dfr,
                           int targetSampleRate);
};

#endif
