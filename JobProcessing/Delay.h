#ifndef DELAY_H
#define DELAY_H

#include "Module.h"
#include "ModuleRecord.h"
#include "SampleValueParameter.h"
#include "ModIn.h"
#include "ModOut.h"

class Delay : public Module {
public:

    /* PARAMETERS (see Delay.java) */

    SampleValueParameter initTime;
    SampleValueParameter initFeedback;
    SampleValueParameter initLevel;

    /* MODINS (see Delay.java) */

    ModIn input {"input"};
    ModIn time {"time"};
    ModIn feedback {"feedback"};
    ModIn level {"level"};

    /* MODOUTS (see Delay.java) */

    ModOut mainOut {"mainOut"};

    /* METHODS and CONSTRUCTORS */

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
