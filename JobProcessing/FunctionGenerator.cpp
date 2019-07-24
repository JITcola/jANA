#include "FunctionGenerator.h"

#include <string>
#include "ModIn.h"
#include "ModOut.h"

Parameter& FunctionGenerator::getParameter(std::string parameterName)
{
    if (parameterName == "baseFrequency")
        return baseFrequency;
    else if (parameterName == "function")
        return function;
    else if (parameterName == "initPhase")
        return initPhase;
    else if (parameterName == "initLevel")
        return initLevel;
    else
        return baseFrequency;
}


ModIn& FunctionGenerator::getModIn(std::string modInName)
{
    if (modInName == "frequency")
        return frequency;
    else if (modInName == "phase")
        return phase;
    else if (modInName == "level")
        return level;
    else
        return frequency;
}

ModOut& FunctionGenerator::getModOut(std::string modOutName)
{
    if (modOutName == "mainOut")
        return mainOut;
    else if (modOutName == "auxOut1")
        return auxOut1;
    else if (modOutName == "auxOut2")
        return auxOut2;
    else if (modOutName == "auxOut3")
        return auxOut3;
    else
        return mainOut;
}
