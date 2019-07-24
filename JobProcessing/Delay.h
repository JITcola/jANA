#ifndef DELAY_H
#define DELAY_H

#include <string>

#include "Module.h"
#include "ModuleRecord.h"
#include "SampleValueParameter.h"
#include "ModIn.h"
#include "ModOut.h"
#include "ModuleType.h"

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
    
    ModIn& getModIn(std::string name);
    ModOut& getModOut(std::string name);

    Delay(bool isMultiprecision, 
          int multiprecisionBits,
          std::vector<SampleValue>& time, 
          ModuleRecord& moduleRecord)
        : Module(ModuleType::Delay, isMultiprecision, 
                 multiprecisionBits, time),
          initTime {moduleRecord.getSampleValueParameter("initTime")},
          initFeedback {moduleRecord.getSampleValueParameter("initFeedback")},
          initLevel {moduleRecord.getSampleValueParameter("initLevel")}
    {}
};

#endif
