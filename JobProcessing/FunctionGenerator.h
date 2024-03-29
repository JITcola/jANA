#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H

#include <string>

#include "Module.h"
#include "ModuleRecord.h"
#include "SampleValueParameter.h"
#include "OptionParameter.h"
#include "ModIn.h"
#include "ModOut.h"
#include "ModuleType.h"

class FunctionGenerator : public Module {
public:

    /* PARAMETERS (see FunctionGenerator.java) */

    SampleValueParameter baseFrequency;
    OptionParameter function;
    SampleValueParameter initPhase;
    SampleValueParameter initLevel;

    /* MODINS (see FunctionGenerator.java) */

    ModIn frequency {"frequency"};
    ModIn phase {"phase"};
    ModIn level {"level"};

    /* MODOUTS (see FunctionGenerator.java) */

    ModOut mainOut {"mainOut"};
    ModOut auxOut1 {"auxOut1"};
    ModOut auxOut2 {"auxOut2"};
    ModOut auxOut3 {"auxOut3"};

    /* METHODS and CONSTRUCTORS */

    void computeNextSample() { return; }

    Parameter& getParameter(std::string parameterName);
    ModIn& getModIn(std::string modInName);
    ModOut& getModOut(std::string modOutName);

    FunctionGenerator(bool isMultiprecision, int multiprecisionBits,
                      std::vector<SampleValue>& time, 
                      ModuleRecord& moduleRecord)
        : Module(ModuleType::FunctionGenerator, isMultiprecision, 
                 multiprecisionBits, time),
          baseFrequency {
              moduleRecord.getSampleValueParameter(
              "baseFrequency", isMultiprecision, multiprecisionBits)
          },
          function {moduleRecord.getOptionParameter("function")},
          initPhase {moduleRecord.getSampleValueParameter(
              "initPhase", isMultiprecision, multiprecisionBits)
          },
          initLevel {moduleRecord.getSampleValueParameter(
              "initLevel", isMultiprecision, multiprecisionBits)
          }
    {}
};

#endif
