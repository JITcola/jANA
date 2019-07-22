#ifndef DELAY_H
#define DELAY_H

#include "Module.h"
#include "ModuleRecord.h"
#include "SampleValueParameter.h"

class Delay : public Module {
public:
    SampleValueParameter initTime;
    SampleValueParameter initFeedback;
    SampleValueParameter initLevel;

    void computeNextSample() { return; }
    Delay(bool isMultiprecision, 
          int multiprecisionBits,
          std::vector<SampleValue>& time, 
          ModuleRecord& moduleRecord)
        : Module(isMultiprecision, multiprecisionBits, time),
          initTime {moduleRecord.getSampleValueParameter("initTime")},
          initFeedback {moduleRecord.getSampleValueParameter("initFeedback")},
          initLevel {moduleRecord.getSampleValueParameter("initLevel")}
    {}
};

#endif
