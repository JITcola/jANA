#include "Delay.h"

#include <string>
#include "ModIn.h"
#include "ModOut.h"

Parameter& Delay::getParameter(std::string parameterName)
{
    if (parameterName == "initTime")
        return initTime;
    else if (parameterName == "initFeedback")
        return initFeedback;
    else if (parameterName == "initLevel")
        return initLevel;
    else
        return initTime;
}


ModIn& Delay::getModIn(std::string modInName)
{
    if (modInName == "input")
        return input;
    else if (modInName == "time")
        return time;
    else if (modInName == "feedback")
        return feedback;
    else if (modInName == "level")
        return level;
    else
        return input;
}

ModOut& Delay::getModOut(std::string modOutName)
{
    if (modOutName == "mainOut")
        return mainOut;
    else
        return mainOut;
}
